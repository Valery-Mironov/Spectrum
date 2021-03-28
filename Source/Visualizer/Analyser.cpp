#include "Analyser.h"

Analyser::Analyser( ValueTree &audioProcessorValueTreeState ) :
    mr_valueTree( audioProcessorValueTreeState ),
    m_forwardFFT_11( 11 ),
    m_forwardFFT_12( 12 ),
    m_forwardFFT_13( 13 ),
    m_forwardFFT_14( 14 ),
    m_window_2048( 2048, juce::dsp::WindowingFunction<float>::hann ),
    m_window_4096( 4096, juce::dsp::WindowingFunction<float>::hann ),
    m_window_8192( 8192, juce::dsp::WindowingFunction<float>::hann ),
    m_window_16384( 16384, juce::dsp::WindowingFunction<float>::hann )
{
    auto selectedComboBoxIndex
    {
        mr_valueTree.getRawParameterValue( "BLOCK_ID" )->load()
    };
    
    setFFTBlockSize( static_cast<int>( selectedComboBoxIndex ) );
    
    mr_valueTree.addParameterListener( "BLOCK_ID", this );
    mr_valueTree.addParameterListener( "LEFT_ID", this );
    mr_valueTree.addParameterListener( "RIGHT_ID", this );
    mr_valueTree.addParameterListener( "BOTH_ID", this );
    mr_valueTree.addParameterListener( "AVG_ID", this );
    mr_valueTree.addParameterListener( "RANGE_ID", this );
    mr_valueTree.addParameterListener( "MAXIMUM_ID", this );
    mr_valueTree.addParameterListener( "MINIMUM_ID", this );
}


// ============================================================================
void Analyser::resetScopeMaximumsData()
{
    const juce::ScopedLock lock( m_volumeRangeChange );
    
    auto minimum { m_minimumVolumeInDecibels };
    
    for ( auto &data : m_volumsMaximumData )
    {
        data = minimum;
    }
    
    m_currentMaximumVolumeInDecibels.store( minimum );
    m_currentAverageVolumeInDecibels.store( minimum );
}


// ============================================================================
void Analyser::setNextFFTBlockStatus( const bool nextFFTBlockStatus )
{
    m_nextFFTBlockReady.store( nextFFTBlockStatus );
}



bool Analyser::getNextFFTBlockStatus()
{
    return m_nextFFTBlockReady.load() && m_blockSizeDefined.load();
}


// ============================================================================
size_t Analyser::getScopeSize()
{
    return m_scopeDynamicData.size();
}



float Analyser::getScopeData( size_t index )
{
    return m_scopeDynamicData.at( index );
}



float Analyser::getScopeMaximumsData( size_t index )
{
    return m_scopeMaximumData.at( index );
}



float Analyser::getOffset()
{
    return m_offset.load();
}


// ============================================================================
void Analyser::pushSamplesIntoFifo(
    const float leftChannel,
    const float rightChannel
) noexcept {
    float dataForAnalysis;
    
    switch ( m_activeChannels.load() ) {
        case Channels::left:
            dataForAnalysis = leftChannel;
            break;
        case Channels::right:
            dataForAnalysis = rightChannel;
            break;
        case Channels::both:
            dataForAnalysis =  ( leftChannel + rightChannel ) / 2.0f;
            break;
        default:
            DBG( "Error! Unknown channel." );
            break;
    }
    
    if ( m_blockSizeDefined.load() )
    {
        if ( m_fftSize.load() == m_fifoIndex.load() )
        {
            if ( ! m_nextFFTBlockReady.load() )
            {
                m_fftData.clear();
                m_fftData.swap( m_fifo );
                m_fftData.resize( m_fftSize.load() * 2 );
                m_nextFFTBlockReady.store( true );
            }
            m_fifo.clear();
            m_fifoIndex.store( 0 );
        }
        ++m_fifoIndex;
        m_fifo.push_back( dataForAnalysis );
    }
}



void Analyser::calculateNextFrameOfSpectrum()
{
    processFFT();
    calculateCurrentVolumes();
    calculateDynamicVolumes();
    calculateMaximumVolumes();
    
    if ( m_volumeRangeIsDynamamic )
    {
        auto maximum = mr_valueTree.getParameter( "MAXIMUM_ID" );
        maximum->
            setValueNotifyingHost(
                juce::jmap(
                    m_currentMaximumVolumeInDecibels.load(),
                    -200.0f,
                    40.0f,
                    0.0f,
                    1.0f
                )
            );
        
        calculateCurrentAverageVolume();
        
        auto minumum = mr_valueTree.getParameter( "MINIMUM_ID" );
        minumum->
            setValueNotifyingHost(
                juce::jmap(
                    m_currentAverageVolumeInDecibels.load(),
                    -380.0f,
                    30.0f,
                    0.0f,
                    1.0f
                )
            );
    }
    
    m_scopeDynamicData.clear();
    for ( const auto &data : m_volumsDynamicData )
    {
        m_scopeDynamicData.push_back( adaptData( data ) );
    }
        
    m_scopeMaximumData.clear();
    for ( const auto &data : m_volumsMaximumData )
    {
        m_scopeMaximumData.push_back( adaptData( data ) );
    }
}


// ============================================================================
void Analyser::processFFT()
{
    switch ( m_fftSize.load() ) {
        case 2048:
            m_window_2048.multiplyWithWindowingTable(
                m_fftData.data(),
                m_fftSize.load()
            );
            m_forwardFFT_11.performFrequencyOnlyForwardTransform(
                m_fftData.data()
            );
            break;
        case 4096:
            m_window_4096.multiplyWithWindowingTable(
                m_fftData.data(),
                m_fftSize.load()
            );
            m_forwardFFT_12.performFrequencyOnlyForwardTransform(
                m_fftData.data()
            );
            break;
        case 8192:
            m_window_8192.multiplyWithWindowingTable(
                m_fftData.data(),
                m_fftSize.load()
            );
            m_forwardFFT_13.performFrequencyOnlyForwardTransform(
                m_fftData.data()
            );
            break;
        case 16384:
            m_window_16384.multiplyWithWindowingTable(
                m_fftData.data(),
                m_fftSize.load()
            );
            m_forwardFFT_14.performFrequencyOnlyForwardTransform(
                m_fftData.data()
            );
            break;
        default:
            DBG( "FFT Size erorr!" );
            break;
    }
}


// ============================================================================
void Analyser::calculateCurrentVolumes()
{
    auto scopeSize { m_scopeSize.load() };
    auto scopeSizeAsFloat { static_cast<float>( scopeSize ) };
    auto offset { juce::Decibels::gainToDecibels( scopeSizeAsFloat ) };
    
    m_avgData[ m_avgFifoWritePointer.load() ].clear();
    
    for ( int i { 0 }; i < m_fftSize.load() / 2; ++i )
    {
        auto fftData { m_fftData.at( i ) };
        auto data { juce::Decibels::gainToDecibels( fftData ) };
        auto currentVolumeInDecibels { data - offset };
        
        m_avgData[ m_avgFifoWritePointer.load() ].push_back( currentVolumeInDecibels );
    }
    
    if ( m_avgFifoSize.load() != m_avgFactor.load() ) { ++m_avgFifoSize; }
    
    m_avgFifoReadPointer = m_avgFifoWritePointer.load();
    
    if ( m_avgFifoWritePointer.load() + 1 < m_avgFifoMaximumSize )
    {
        ++m_avgFifoWritePointer;
    }
    else
    {
        m_avgFifoWritePointer.store( 0 );
    }
}



void Analyser::calculateDynamicVolumes()
{
    m_volumsDynamicData.clear();
    
    for ( auto data { 0 }; data < m_scopeSize.load(); ++data )
    {
        auto sum { 0.0f };
        auto tempReadPointer { m_avgFifoReadPointer };
        
        for ( auto counter { m_avgFifoSize.load() }; 0 < counter; --counter )
        {
            sum += m_avgData[ tempReadPointer ].at( data );
            
            tempReadPointer == 0 ?
            tempReadPointer = m_avgFifoMaximumSize - 1 :
            --tempReadPointer;
        }
        
        sum /= static_cast<float>( m_avgFifoSize.load() );
        m_volumsDynamicData.push_back( sum );
    }
}



void Analyser::calculateMaximumVolumes()
{
    for ( auto i { 0 }; i < m_scopeSize.load(); ++i ) {
        if ( m_volumsMaximumData.at( i ) < m_volumsDynamicData.at( i ) )
        {
            m_volumsMaximumData[ i ] = m_volumsDynamicData.at( i );
        }
        if ( m_currentMaximumVolumeInDecibels.load() < m_volumsMaximumData.at( i ) )
        {
            m_currentMaximumVolumeInDecibels.store( m_volumsMaximumData.at( i ) );
        }
    }
}



void Analyser::calculateCurrentAverageVolume()
{
    m_currentAverageVolumeInDecibels.store(
        m_currentMaximumVolumeInDecibels.load() - 10.0f
    );
    
    for ( const auto &volume : m_volumsDynamicData )
    {
        m_currentAverageVolumeInDecibels.store(
            m_currentAverageVolumeInDecibels.load() + volume
        );
    }
    
    {
        const juce::ScopedLock lock( m_volumeRangeChange );
        
        m_currentAverageVolumeInDecibels.store( m_currentAverageVolumeInDecibels.load() /
            static_cast<float>( m_scopeSize.load() )
        );
    }
}



float Analyser::adaptData( const float volume )
{
    const juce::ScopedLock lock( m_volumeRangeChange );
    
    auto data {
        juce::jmap(
            volume,
            m_minimumVolumeInDecibels,
            m_maximumVolumeInDecibels,
            0.0f,
            1.0f )
    };
    
    return data;
}


// ============================================================================
void Analyser::parameterChanged(
    const juce::String &parameterID,
    float newValue )
{
    if ( parameterID == "BLOCK_ID" )
    {
        setFFTBlockSize( static_cast<int>( newValue ) );
    }
    else if ( parameterID == "LEFT_ID" )
    {
        setActiveChannel( Channels::left );
    }
    else if ( parameterID == "RIGHT_ID" )
    {
        setActiveChannel( Channels::right );
    }
    else if ( parameterID == "BOTH_ID" )
    {
        setActiveChannel( Channels::both );
    }
    else if ( parameterID == "AVG_ID" )
    {
        setAvg( static_cast<size_t>( newValue ) );
    }
    else if ( parameterID == "RANGE_ID" )
    {
        setVolumeScaleModeAsDynamic( ! static_cast<bool>( newValue ) );
    }
    else if ( parameterID == "MAXIMUM_ID" || parameterID == "MINIMUM_ID" )
    {
        auto maximum =
            mr_valueTree.getRawParameterValue( "MAXIMUM_ID" )->load();
        auto minimum =
            mr_valueTree.getRawParameterValue( "MINIMUM_ID" )->load();
        
        if ( maximum - 10.0f < minimum ) { minimum = maximum - 10.0f; }
        
        setVolumeRangeInDecibels( maximum, minimum );
    }
}


// ============================================================================
void Analyser::setFFTBlockSize( const int blockMenuIndex )
{
    m_blockSizeDefined.store( false );
    
    // FFT size 2048:   index 1 = 23.4375 Hz
    // FFT size 4096:   index 2 = 23.4375 Hz
    // FFT size 8192:   index 4 = 23.4375 Hz
    // FFT size 16384:  index 8 = 23.4375 Hz
    
    switch ( blockMenuIndex )
    {
        case 0: m_fftOrder.store( 11 ); m_offset.store( 1.0f ); break;
        case 1: m_fftOrder.store( 12 ); m_offset.store( 2.0f ); break;
        case 2: m_fftOrder.store( 13 ); m_offset.store( 4.0f ); break;
        case 3: m_fftOrder.store( 14 ); m_offset.store( 8.0f ); break;
        default: DBG("Unknown block menu index"); break;
    }
    
    m_fftSize.store( 1 << m_fftOrder );
    m_scopeSize.store( m_fftSize.load() / 2 );
    m_fifoIndex.store( 0 );
    
    m_fifo.resize( m_fftSize.load() );
    m_fftData.resize( m_fftSize.load() * 2 );
    
    {
        const juce::ScopedLock lock( m_volumeRangeChange );
        
        m_volumsDynamicData.resize(
            m_scopeSize.load(),
            m_minimumVolumeInDecibels
        );
        m_volumsMaximumData.resize(
            m_scopeSize.load(),
            m_minimumVolumeInDecibels
        );
    }
    
    m_scopeDynamicData.resize(
        m_scopeSize.load(),
        0
    );
    m_scopeMaximumData.resize(
        m_scopeSize.load(),
        0
    );
    
    {
        const juce::ScopedLock lock( m_volumeRangeChange );
        
        for ( auto &vector : m_avgData )
        {
            vector.resize( m_scopeSize.load(), m_minimumVolumeInDecibels );
        }
    }
    
    m_avgFifoSize.store( 0 );
    m_avgFifoWritePointer.store( 0 );
    
    resetScopeMaximumsData();
    
    m_blockSizeDefined.store( true );
}



void Analyser::setActiveChannel( Channels channels )
{
    m_activeChannels.store( channels );
}



void Analyser::setAvg( size_t avg )
{
    m_avgFactor.store( avg );
    m_avgFifoSize.store( avg );
}



void Analyser::setVolumeScaleModeAsDynamic( bool isDynamamic )
{
    m_volumeRangeIsDynamamic.store( isDynamamic );
    resetScopeMaximumsData();
}



void Analyser::setVolumeRangeInDecibels( float maximum, float minimum )
{
    const juce::ScopedLock lock( m_volumeRangeChange );
    
    m_maximumVolumeInDecibels = maximum;
    m_minimumVolumeInDecibels = minimum;
}
