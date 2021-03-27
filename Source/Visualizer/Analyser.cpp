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
    mr_valueTree.addParameterListener( "LEFT_ID", this );
    mr_valueTree.addParameterListener( "RIGHT_ID", this );
    mr_valueTree.addParameterListener( "LEFT_PLUS_RIGHT_ID", this );
    mr_valueTree.addParameterListener( "BLOCK_ID", this );
    mr_valueTree.addParameterListener( "RANGE_ID", this );
    mr_valueTree.addParameterListener( "MAXIMUM_ID", this );
    mr_valueTree.addParameterListener( "MINIMUM_ID", this );
    
    auto selectedComboBoxIndex
    {
        mr_valueTree.getRawParameterValue( "BLOCK_ID" )->load()
    };
    
    setFFTBlockSize( static_cast<int>( selectedComboBoxIndex ) );
}


// ============================================================================
void Analyser::resetScopeMaximumsData()
{
    for ( auto &data : m_volumsMaximumData )
    {
        data = m_minimumVolumeInDecibels;
    }
    
    m_currentMaximumVolumeInDecibels = m_minimumVolumeInDecibels;
    m_currentMinimumVolumeInDecibels = m_minimumVolumeInDecibels;
}


// ============================================================================
void Analyser::setNextFFTBlockStatus( const bool nextFFTBlockStatus )
{
    m_nextFFTBlockReady = nextFFTBlockStatus;
}



bool Analyser::getNextFFTBlockStatus()
{
    return m_nextFFTBlockReady && m_blockSizeDefined;
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



float Analyser::getcurrentMaximumInDecibels()
{
    return m_currentMaximumVolumeInDecibels;
}



float Analyser::getOffset()
{
    return m_offset;
}


// ============================================================================
void Analyser::pushSamplesIntoFifo(
    float leftChannel,
    float rightChannel ) noexcept
{
    float dataForAnalysis;
    
    if ( m_activeChannel == e_left ) { dataForAnalysis = leftChannel; }
    else if ( m_activeChannel == e_right ) { dataForAnalysis = rightChannel; }
    else { dataForAnalysis = ( leftChannel + rightChannel ) / 2.0f; }
    
    if ( m_blockSizeDefined )
    {
        if ( m_fftSize == m_fifoIndex)
        {
            if ( ! m_nextFFTBlockReady )
            {
                m_fftData.clear();
                m_fftData.swap( m_fifo );
                m_fftData.resize( m_fftSize * 2 );
                m_nextFFTBlockReady = true;
            }
            m_fifo.clear();
            m_fifoIndex = 0;
        }
        m_fifoIndex++;
        m_fifo.push_back( dataForAnalysis );
    }
}



void Analyser::calculateNextFrameOfSpectrum()
{
    processFFT();
    calculateDynamicVolumes();
    calculateMaximumVolumes();
    
    if ( m_volumeRangeIsDynamamic )
    {
        auto maximum = mr_valueTree.getParameter( "MAXIMUM_ID" );
        maximum->
            setValueNotifyingHost(
                juce::jmap(
                    m_currentMaximumVolumeInDecibels,
                    -200.0f,
                    40.0f,
                    0.0f,
                    1.0f ) );
        
        calculateMinimumVolume();
        
        auto minumum = mr_valueTree.getParameter( "MINIMUM_ID" );
        minumum->
            setValueNotifyingHost(
                juce::jmap(
                    m_currentMinimumVolumeInDecibels,
                    -380.0f,
                    30.0f,
                    0.0f,
                    1.0f ) );
    }
    
    m_scopeDynamicData.clear();
    for ( auto &data : m_volumsDynamicData ) {
        m_scopeDynamicData.push_back( adaptData( data ) );
    }
    
    m_scopeMaximumData.clear();
    for ( auto &data : m_volumsMaximumData ) {
        m_scopeMaximumData.push_back( adaptData( data ) );
    }
}


// ============================================================================
void Analyser::processFFT()
{
    switch ( m_fftSize ) {
        case 2048:
            m_window_2048.multiplyWithWindowingTable(
                m_fftData.data(),
                m_fftSize );
            m_forwardFFT_11.performFrequencyOnlyForwardTransform(
                m_fftData.data() );
            break;
        case 4096:
            m_window_4096.multiplyWithWindowingTable(
                m_fftData.data(),
                m_fftSize );
            m_forwardFFT_12.performFrequencyOnlyForwardTransform(
                m_fftData.data() );
            break;
        case 8192:
            m_window_8192.multiplyWithWindowingTable(
                m_fftData.data(),
                m_fftSize );
            m_forwardFFT_13.performFrequencyOnlyForwardTransform(
                m_fftData.data() );
            break;
        case 16384:
            m_window_16384.multiplyWithWindowingTable(
                m_fftData.data(),
                m_fftSize );
            m_forwardFFT_14.performFrequencyOnlyForwardTransform(
                m_fftData.data() );
            break;
        default:
            DBG("FFT Size erorr!");
            break;
    }
}



void Analyser::calculateDynamicVolumes()
{
    auto scopeSizeAsFloat { static_cast<float>( m_scopeSize ) };
    auto offset { juce::Decibels::gainToDecibels( scopeSizeAsFloat ) };
    
    m_volumsDynamicData.clear();
    
    for ( int i { 0 }; i < m_fftSize / 2; ++i )
    {
        auto fftData { m_fftData.at( i ) };
        auto data { juce::Decibels::gainToDecibels( fftData ) };
        auto currentVolumeInDecibels { data - offset };
        
        m_volumsDynamicData.push_back( currentVolumeInDecibels );
    }
}



void Analyser::calculateMaximumVolumes()
{
    for ( auto i { 0 }; i < m_scopeSize; ++i ) {
        if ( m_volumsMaximumData.at( i ) < m_volumsDynamicData.at( i ) )
        {
            m_volumsMaximumData[ i ] = m_volumsDynamicData.at( i );
        }
        if ( m_currentMaximumVolumeInDecibels < m_volumsMaximumData.at( i ) )
        {
            m_currentMaximumVolumeInDecibels = m_volumsMaximumData.at( i );
        }
    }
}



void Analyser::calculateMinimumVolume()
{
    m_currentMinimumVolumeInDecibels =
        m_currentMaximumVolumeInDecibels - 10.0f;
    
    for ( const auto &volume : m_volumsDynamicData )
    {
        m_currentMinimumVolumeInDecibels += volume;
    }
    
    
    m_currentMinimumVolumeInDecibels /= static_cast<float>( m_scopeSize );
}


float Analyser::adaptData( float volume )
{
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
        setActiveChannel( e_left );
    }
    else if ( parameterID == "RIGHT_ID" )
    {
        setActiveChannel( e_right );
    }
    else if ( parameterID == "LEFT_PLUS_RIGHT_ID" )
    {
        setActiveChannel( e_leftPlusRight );
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
        
        if ( maximum - 10 < minimum ) { minimum = maximum - 10; }
        
        setVolumeRangeInDecibels( maximum, minimum );
    }
}


// ============================================================================
void Analyser::setFFTBlockSize( int blockMenuIndex )
{
    m_blockSizeDefined = false;
    
    // FFT size 2048:   index 1 = 23.4375 Hz
    // FFT size 4096:   index 2 = 23.4375 Hz
    // FFT size 8192:   index 4 = 23.4375 Hz
    // FFT size 16384:  index 8 = 23.4375 Hz
    
    switch ( blockMenuIndex )
    {
        case 0: m_fftOrder = 11; m_offset = 1.0f; break;
        case 1: m_fftOrder = 12; m_offset = 2.0f; break;
        case 2: m_fftOrder = 13; m_offset = 4.0f; break;
        case 3: m_fftOrder = 14; m_offset = 8.0f; break;
        default: DBG("Unknown block menu index"); break;
    }
    
    m_fftSize = 1 << m_fftOrder;
    m_scopeSize = m_fftSize / 2;
    m_fifoIndex = 0;
    
    m_fifo.resize( m_fftSize );
    m_fftData.resize( m_fftSize * 2 );
    m_volumsDynamicData.resize( m_scopeSize );
    m_volumsMaximumData.resize( m_scopeSize );
    m_scopeDynamicData.resize( m_scopeSize );
    m_scopeMaximumData.resize( m_scopeSize );
    
    resetScopeMaximumsData();
    
    m_blockSizeDefined = true;
}



void Analyser::setActiveChannel( int channel )
{
    m_activeChannel = channel;
}



void Analyser::setVolumeScaleModeAsDynamic( bool isDynamamic )
{
    m_volumeRangeIsDynamamic = isDynamamic;
    resetScopeMaximumsData();
}



void Analyser::setVolumeRangeInDecibels( float maximum, float minimum )
{
    m_maximumVolumeInDecibels = maximum;
    m_minimumVolumeInDecibels = minimum;
}
