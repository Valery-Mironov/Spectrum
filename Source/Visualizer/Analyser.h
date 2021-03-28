#pragma once

#include <JuceHeader.h>

using ValueTree = juce::AudioProcessorValueTreeState;

// ****************************************************************************
// ANALYSER CLASS
// ****************************************************************************
class Analyser : public ValueTree::Listener
{
public:
    enum class Channels { left, right, both };
    
    
    // ========================================================================
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
    float getOffset();
    
    
    // ========================================================================
    void pushSamplesIntoFifo( const float, const float ) noexcept;
    void calculateNextFrameOfSpectrum();
    
private:
    // ========================================================================
    void processFFT();
    void calculateCurrentVolumes();
    void calculateDynamicVolumes();
    void calculateMaximumVolumes();
    void calculateCurrentAverageVolume();
    float adaptData( float );
    
    
    // ========================================================================
    void parameterChanged( const juce::String &, float ) override;
    
    
    // ========================================================================
    void setFFTBlockSize( int );
    void setActiveChannel( Channels );
    void setAvg( size_t );
    void setVolumeScaleModeAsDynamic( bool );
    void setVolumeRangeInDecibels( float, float );
    
    
    // ========================================================================
    ValueTree &mr_valueTree;
    
    juce::dsp::FFT m_forwardFFT_11;
    juce::dsp::FFT m_forwardFFT_12;
    juce::dsp::FFT m_forwardFFT_13;
    juce::dsp::FFT m_forwardFFT_14;
    
    juce::dsp::WindowingFunction<float> m_window_2048;
    juce::dsp::WindowingFunction<float> m_window_4096;
    juce::dsp::WindowingFunction<float> m_window_8192;
    juce::dsp::WindowingFunction<float> m_window_16384;
    
    std::atomic<size_t> m_fftOrder;
    std::atomic<size_t> m_fftSize;
    std::atomic<size_t> m_scopeSize;
    std::atomic<size_t> m_fifoIndex;
    
    std::atomic<Channels> m_activeChannels { Channels::both };
    
    std::atomic<bool> m_blockSizeDefined { false };
    std::atomic<bool> m_nextFFTBlockReady { false };
    std::atomic<bool> m_volumeRangeIsDynamamic { false };
    std::atomic<bool> m_frequencyIsLogarithmic { true };
    
    std::vector<float> m_fifo;
    std::vector<float> m_fftData;
    std::vector<float> m_volumsDynamicData;
    std::vector<float> m_volumsMaximumData;
    std::vector<float> m_scopeDynamicData;
    std::vector<float> m_scopeMaximumData;
    
    std::atomic<size_t> m_avgFactor { 1 };
    std::atomic<size_t> m_avgFifoSize { 0 };
    std::atomic<size_t> m_avgFifoWritePointer { 0 };
    size_t              m_avgFifoReadPointer;
    static const size_t m_avgFifoMaximumSize { 16 };
    
    std::array<std::vector<float>, m_avgFifoMaximumSize> m_avgData;
    
    juce::CriticalSection m_volumeRangeChange;
    float m_maximumVolumeInDecibels { 12.0f };
    float m_minimumVolumeInDecibels { -120.0f };
    
    std::atomic<float> m_offset;
    std::atomic<float> m_currentMaximumVolumeInDecibels;
    std::atomic<float> m_currentAverageVolumeInDecibels;
    
    
    // ========================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR( Analyser )
};
