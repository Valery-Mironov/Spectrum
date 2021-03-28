#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "Controls/Controls.h"
#include "Visualizer/Visualizer.h"

// ****************************************************************************
// SPECTRUM AUDIO PROCESSOR EDITOR CLASS
// ****************************************************************************
class SpectrumAudioProcessorEditor : public juce::AudioProcessorEditor
{
public:
    SpectrumAudioProcessorEditor(
        SpectrumAudioProcessor &,
        juce::AudioProcessorValueTreeState &,
        Analyser &
    );
    
    
    
    ~SpectrumAudioProcessorEditor() override;
    
    
    // ========================================================================
    void paint( juce::Graphics & ) override;
    void resized() override;
    
    
private:
    // ========================================================================
    SpectrumAudioProcessor &mr_audioProcessor;
    
    Visualizer m_visualizer;
    Controls m_controls;
    
    juce::Colour backgroundColour { 0xffd2d2d2 };
    
    static constexpr double m_marginInPixels { 10 };
    
    
    // ========================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR( SpectrumAudioProcessorEditor )
};
