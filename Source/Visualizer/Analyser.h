#pragma once

#include <JuceHeader.h>

// ****************************************************************************
// ANALYSER CLASS
// ****************************************************************************
class Analyser
{
public:
    Analyser();
    
    
    // ========================================================================
    void pushNextSampleIntoFifo( float sample ) noexcept;
    void drawNextFrameOfSpectrum();
    
    
    // ========================================================================
    bool getNextFFTBlockStatus();
    void setNextFFTBlockStatus( const bool nextFFTBlockStatus );
    
    
    // ========================================================================
    float getScopeData( size_t index );
    float getOffset();
    size_t getScopeSize();
    
    
    // ========================================================================
    void setFFTBlockSize( size_t newFFTOrder );
    
private:
    // ========================================================================
    void drawFrame( juce::Graphics &g );
    
    
    // ========================================================================
    float m_offset;
    
    size_t m_fftOrder;
    size_t m_fftSize;
    size_t m_scopeSize;
    size_t m_fifoIndex;
    
    bool m_nextFFTBlockReady { false };
    bool m_blockSizeDefined { false };
    
    std::vector<float> m_fifo;
    std::vector<float> m_fftData;
    std::vector<float> m_scopeData;
    
    
    // ========================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR( Analyser )
};
