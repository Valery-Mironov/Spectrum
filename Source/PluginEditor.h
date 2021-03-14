#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "Controls/Controls.h"
#include "Visualizer/Visualizer.h"

// ****************************************************************************
// SPECTRUM AUDIO PROCESSOR EDITOR CLASS
// ****************************************************************************
class SpectrumAudioProcessorEditor :
    public juce::AudioProcessorEditor
{
public:
    SpectrumAudioProcessorEditor( SpectrumAudioProcessor &p, Analyser &v );
    ~SpectrumAudioProcessorEditor() override;
    
    // ========================================================================
    void paint( juce::Graphics &g ) override;
    void resized() override;

private:
    // ========================================================================
    SpectrumAudioProcessor &mr_audioProcessor;
    Controls m_controls;
    Visualizer m_visualizer;
    
    // Must be set by the 'set' method
    juce::Colour backgroundColour { 0xffd2d2d2 };
    
    // Must be set by the 'set' method
    static constexpr double m_marginInPixels { 10 };
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR( SpectrumAudioProcessorEditor )
};
