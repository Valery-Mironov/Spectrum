#pragma once

#include <JuceHeader.h>

/*
    TASKS
    
    Speed up calculations for large "Block" values
    Correct volumes when switching "Channel"
    Setting "Avg" by the nearest 1-8 volume values
    Automatic calculation of volume limiters for "Auto" mode in "Scale Y"
    Manual setting of limiters via the "Scale Y" sliders
*/

// ****************************************************************************
// ANALYSER CLASS
// ****************************************************************************
class Analyser
{
public:
    Analyser();
    
    
    // ========================================================================
    void setChannels( int selectedChannels );
    
    
    // ========================================================================
    void setFFTBlockSize( size_t newFFTOrder );
    
    
    // ========================================================================
    bool getNextFFTBlockStatus();
    void setNextFFTBlockStatus( const bool nextFFTBlockStatus );
    
    
    // ========================================================================
    size_t getScopeSize();
    float getScopeData( size_t index );
    float getScopeMaximumsData( size_t index );
    void resetScopeMaximumsData();
    float getOffset();
    
    
    // ========================================================================
    void setVolumeScaleDynamicRange( bool isDynamamic );
    void setVolumeRangeInDecibels( float minimum, float maximum );
    
    
    // ========================================================================
    void pushNextSampleIntoFifo(
        float leftChannelSample,
        float rightChannelSample ) noexcept;
    void drawNextFrameOfSpectrum();
    
private:
    // ========================================================================
    void calculateMaximumVolumes();
    
    
    // ========================================================================
    int m_channels;
    
    bool m_blockSizeDefined;
    bool m_nextFFTBlockReady;
    bool m_volumeScaleRangeIsDynamamic;
    
    size_t m_fftOrder;
    size_t m_fftSize;
    size_t m_scopeSize;
    size_t m_fifoIndex;
    
    std::vector<float> m_fifo;
    std::vector<float> m_fftData;
    std::vector<float> m_scopeData;
    std::vector<float> m_scopeMaximumsData;
    
    float m_offset;
    float m_maximumVolumeInDecibels;
    float m_minimumVolumeInDecibels;
    
    
    // ========================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR( Analyser )
};
