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
    void prepareToPlay( double sampleRate, int samplesPerBlock ) override;
    void processBlock (
        juce::AudioBuffer<float> &,
        juce::MidiBuffer & ) override;
    void releaseResources() override;
    
    
#ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported( const BusesLayout &layouts ) const override;
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
    void setCurrentProgram( int index ) override;
    const juce::String getProgramName( int index ) override;
    void changeProgramName( int index, const juce::String &newName ) override;
    
    
    // ========================================================================
    void getStateInformation( juce::MemoryBlock &destData ) override;
    void setStateInformation( const void *data, int sizeInBytes ) override;
    
private:
    // ========================================================================
    Analyser m_analyser;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR( SpectrumAudioProcessor )
};
