#pragma once

#include <JuceHeader.h>

/*
    TASKS
    
    Setting "Avg" by the nearest 1-8 volume values
*/

using ValueTree = juce::AudioProcessorValueTreeState;

// ****************************************************************************
// ANALYSER CLASS
// ****************************************************************************
class Analyser : public ValueTree::Listener
{
public:
    Analyser( ValueTree & );
    
    
    // ========================================================================
    void resetScopeMaximumsData();
    
    
    // ========================================================================
    void setNextFFTBlockStatus( const bool );
    bool getNextFFTBlockStatus();
    
    
    // ========================================================================
    size_t getScopeSize();
    float getScopeData( size_t );
    float getScopeMaximumsData( size_t );
    float getcurrentMaximumInDecibels();
    float getOffset();
    
    
    // ========================================================================
    void pushSamplesIntoFifo( float, float ) noexcept;
    void calculateNextFrameOfSpectrum();
    
private:
    // ========================================================================
    void processFFT();
    void calculateDynamicVolumes();
    void calculateMaximumVolumes();
    void calculateMinimumVolume();
    float adaptData( float );
    
    
    // ========================================================================
    void parameterChanged( const juce::String &, float ) override;
    
    
    // ========================================================================
    void setFFTBlockSize( int );
    void setActiveChannel( int );
    void setVolumeScaleModeAsDynamic( bool );
    void setVolumeRangeInDecibels( float, float );
    
    
    // ========================================================================
    enum Channel { e_left = 0, e_right, e_leftPlusRight };
    
    ValueTree &mr_valueTree;
    
    bool m_blockSizeDefined { false };
    bool m_nextFFTBlockReady { false };
    bool m_volumeRangeIsDynamamic { false };
    bool m_frequencyIsLogarithmic { true };
    
    size_t m_fftOrder;
    size_t m_fftSize;
    size_t m_scopeSize;
    size_t m_fifoIndex;
    
    juce::dsp::FFT m_forwardFFT_11;
    juce::dsp::FFT m_forwardFFT_12;
    juce::dsp::FFT m_forwardFFT_13;
    juce::dsp::FFT m_forwardFFT_14;
    
    juce::dsp::WindowingFunction<float> m_window_2048;
    juce::dsp::WindowingFunction<float> m_window_4096;
    juce::dsp::WindowingFunction<float> m_window_8192;
    juce::dsp::WindowingFunction<float> m_window_16384;
    
    std::vector<float> m_fifo;
    std::vector<float> m_fftData;
    std::vector<float> m_volumsDynamicData;
    std::vector<float> m_volumsMaximumData;
    std::vector<float> m_scopeDynamicData;
    std::vector<float> m_scopeMaximumData;
    
    float m_offset;
    float m_maximumVolumeInDecibels { 12 };
    float m_minimumVolumeInDecibels { -120 };
    float m_currentMaximumVolumeInDecibels;
    float m_currentMinimumVolumeInDecibels;
    int m_activeChannel { e_leftPlusRight };
    
    
    // ========================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR( Analyser )
};
