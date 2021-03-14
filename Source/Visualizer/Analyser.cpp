#include <JuceHeader.h>
#include "Analyser.h"

// ****************************************************************************
// ANALYSER CLASS
// ****************************************************************************
Analyser::Analyser() :
    // 2 ^ 11 = 2048 points
    m_fftOrder( 11 )
{
    setFFTBlockSize( m_fftOrder );
}


// ============================================================================
void Analyser::pushNextSampleIntoFifo( float sample ) noexcept
{
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
        m_fifo.push_back( sample );
    }
}



void Analyser::drawNextFrameOfSpectrum()
{
    juce::dsp::FFT forwardFFT( static_cast<int>( m_fftOrder ) );
    juce::dsp::WindowingFunction<float> window(
        m_fftSize,
        juce::dsp::WindowingFunction<float>::hann);
    
    window.multiplyWithWindowingTable( m_fftData.data(), m_fftSize );
    forwardFFT.performFrequencyOnlyForwardTransform( m_fftData.data() );
    
    auto maximumInDecibels { 12.0f };
    auto minimumInDecibels { -120.0f };
    
    m_scopeData.clear();
    
    for ( int index { 0 }; index < m_fftSize / 2; ++index )
    {
        auto level =
            juce::jmap(
                juce::jlimit(
                    minimumInDecibels,
                    maximumInDecibels,
                    juce::Decibels::gainToDecibels(
                        m_fftData.at( index ) ) -
                    juce::Decibels::gainToDecibels(
                        static_cast<float>( m_fftSize ) ) ),
                minimumInDecibels,
                maximumInDecibels,
                0.0f,
                1.0f );
        
        m_scopeData.push_back( level );
    }
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
float Analyser::getScopeData( size_t index )
{
    return m_scopeData.at( index );
}



size_t Analyser::getScopeSize()
{
    return m_scopeData.size();
}

float Analyser::getOffset()
{
    return m_offset;
}



// ============================================================================
void Analyser::setFFTBlockSize( size_t newFFTOrder )
{
    m_blockSizeDefined = false;
    
    m_fftOrder = newFFTOrder;
    m_fftSize = 1 << m_fftOrder;
    
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
    
    m_blockSizeDefined = true;
}
