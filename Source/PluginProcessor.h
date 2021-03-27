#pragma once

#include <JuceHeader.h>
#include "Visualizer/Analyser.h"

// ****************************************************************************
// SPECTRUM AUDIO PROCESSOR CLASS
// ****************************************************************************
class SpectrumAudioProcessor : public juce::AudioProcessor
{
public:
    SpectrumAudioProcessor();
    ~SpectrumAudioProcessor() override;
    
    
    // ========================================================================
    void prepareToPlay( double, int ) override;
    void processBlock( juce::AudioBuffer<float> &, juce::MidiBuffer & ) override;
    void releaseResources() override;
    
    
#ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported( const BusesLayout & ) const override;
#endif
    
    // ========================================================================
    juce::AudioProcessorEditor *createEditor() override;
    bool hasEditor() const override;
    
    
    // ========================================================================
    const juce::String getName() const override;
    
    
    // ========================================================================
    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;
    
    
    // ========================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram( int ) override;
    const juce::String getProgramName( int ) override;
    void changeProgramName( int, const juce::String & ) override;
    
    
    // ========================================================================
    void getStateInformation( juce::MemoryBlock & ) override;
    void setStateInformation( const void *, int ) override;
    
private:
    // ========================================================================
    juce::AudioProcessorValueTreeState::ParameterLayout createParameters();
    
    
    // ========================================================================
    juce::AudioProcessorValueTreeState m_audioProcessorValueTreeState;
    juce::AudioProcessorValueTreeState::ParameterLayout m_parameterLayout;
    
    Analyser m_analyser;
    
    
    // ========================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR( SpectrumAudioProcessor )
};
