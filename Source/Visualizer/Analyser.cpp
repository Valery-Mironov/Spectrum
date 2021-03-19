#include "Analyser.h"

Analyser::Analyser() :
    // 2 = Channel::SelectedChannels::e_LeftPlusRight
    m_channels( 2 ),
    m_blockSizeDefined( false ),
    m_nextFFTBlockReady( false ),
    m_volumeScaleRangeIsDynamamic( false ),
    // 2 ^ 11 = 2048 points
    m_fftOrder( 11 ),
    m_maximumVolumeInDecibels( 12.0f ),
    m_minimumVolumeInDecibels( -120.0f )
{
    setFFTBlockSize( m_fftOrder );
}


// ============================================================================
void Analyser::setChannels( int selectedChannels )
{
    m_channels = selectedChannels;
    
    std::cout << std::endl;
    std::cout << "----------------> ANALYSER <----------------";
    std::cout << std::endl;
    std::cout << "Selected channels: ";
    
    switch ( m_channels ) {
        case 0:
            std::cout << "left";
            break;
            
        case 1:
            std::cout << "right";
            break;
            
        case 2:
            std::cout << "left and right";
            break;
            
        default:
            std::cout << "error";
            break;
    }
    
    std::cout << std::endl;
}


// ============================================================================
void Analyser::setFFTBlockSize( size_t newFFTOrder )
{
    m_blockSizeDefined = false;
    
    m_fftOrder = newFFTOrder;
    m_fftSize = 1 << m_fftOrder;
    
    std::cout << std::endl;
    std::cout << "----------------> ANALYSER <----------------";
    std::cout << std::endl;
    std::cout << "FFT block size: ";
    std::cout << m_fftSize;
    std::cout << std::endl;
    
    // FFT Size 2048:   index 1 = 23.4375 Hz
    // FFT Size 4096:   index 2 = 23.4375 Hz
    // FFT Size 8192:   index 4 = 23.4375 Hz
    // FFT Size 16384:  index 8 = 23.4375 Hz
    
    // Any FFT Size:    index m_fftSize = 48000
    
    switch ( m_fftOrder ) {
        case 11:
            m_offset = 1.0f;
            break;
            
        case 12:
            m_offset = 2.0f;
            break;
            
        case 13:
            m_offset = 4.0f;
            break;
            
        case 14:
            m_offset = 8.0f;
            
        default:
            break;
    }
    
    m_scopeSize = m_fftSize / 2;
    
    m_fifoIndex = 0;
    
    m_fifo.resize( m_fftSize );
    m_fftData.resize( m_fftSize * 2 );
    m_scopeData.resize( m_scopeSize );
    m_scopeMaximumsData.resize( m_scopeSize );
    
    m_blockSizeDefined = true;
}


// ============================================================================
bool Analyser::getNextFFTBlockStatus()
{
    return ( m_nextFFTBlockReady && m_blockSizeDefined );
}



void Analyser::setNextFFTBlockStatus( const bool nextFFTBlockStatus )
{
    m_nextFFTBlockReady = nextFFTBlockStatus;
}


// ============================================================================
size_t Analyser::getScopeSize()
{
    return m_scopeData.size();
}



float Analyser::getScopeData( size_t index )
{
    return m_scopeData.at( index );
}



float Analyser::getScopeMaximumsData( size_t index )
{
    return m_scopeMaximumsData.at( index );
}



void Analyser::resetScopeMaximumsData()
{
    for ( auto &data : m_scopeMaximumsData )
    {
        data = 0;
    }
}


float Analyser::getOffset()
{
    return m_offset;
}


// ============================================================================
void Analyser::setVolumeScaleDynamicRange( bool isDynamamic )
{
    m_volumeScaleRangeIsDynamamic = isDynamamic;
    
    std::cout << std::endl;
    std::cout << "----------------> ANALYSER <----------------";
    std::cout << std::endl;
    std::cout << "Volume scale range is dynamamic: ";
    std::cout << std::boolalpha << m_volumeScaleRangeIsDynamamic;
    std::cout << std::endl;
}

void Analyser::setVolumeRangeInDecibels( float minimum, float maximum )
{
    m_maximumVolumeInDecibels = maximum;
    m_minimumVolumeInDecibels = minimum;
    
    std::cout << std::endl;
    std::cout << "----------------> ANALYSER <----------------";
    std::cout << std::endl;
    std::cout << "Maximum volume in decibels: ";
    std::cout << m_maximumVolumeInDecibels;
    std::cout << std::endl;
    std::cout << "Minimum volume in decibels: ";
    std::cout << m_minimumVolumeInDecibels;
    std::cout << std::endl;
}


// ============================================================================
void Analyser::pushNextSampleIntoFifo(
    float leftChannelSample,
    float rightChannelSample ) noexcept
{
    float dataForAnalysis;
    switch (m_channels) {
        case 0:
            dataForAnalysis = leftChannelSample;
            break;
            
        case 1:
            dataForAnalysis = rightChannelSample;
            break;
            
        case 2:
            dataForAnalysis = leftChannelSample + rightChannelSample;
            break;
            
        default:
            DBG( "Channels switch error!" );
            break;
    }
    
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


// ============================================================================
void Analyser::drawNextFrameOfSpectrum()
{
    juce::dsp::FFT forwardFFT( static_cast<int>( m_fftOrder ) );
    juce::dsp::WindowingFunction<float> window(
        m_fftSize,
        juce::dsp::WindowingFunction<float>::hann);
    
    window.multiplyWithWindowingTable( m_fftData.data(), m_fftSize );
    forwardFFT.performFrequencyOnlyForwardTransform( m_fftData.data() );
    
    m_scopeData.clear();
    
    for ( int index { 0 }; index < m_fftSize / 2; ++index )
    {
        auto level =
            juce::jmap(
                juce::jlimit(
                    m_minimumVolumeInDecibels,
                    m_maximumVolumeInDecibels,
                    juce::Decibels::gainToDecibels(
                        m_fftData.at( index ) ) -
                    juce::Decibels::gainToDecibels(
                        static_cast<float>( m_fftSize ) ) ),
                m_minimumVolumeInDecibels,
                m_maximumVolumeInDecibels,
                0.0f,
                1.0f );
        
        m_scopeData.push_back( level );
    }
    
    calculateMaximumVolumes();
}


void Analyser::calculateMaximumVolumes()
{
    for ( auto index { 0 }; index < m_scopeSize; ++index ) {
        if ( m_scopeMaximumsData.at( index ) < m_scopeData.at( index ) )
        {
            m_scopeMaximumsData[ index ] = m_scopeData.at( index );
        }
    }
}
