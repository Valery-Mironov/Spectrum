#pragma once

#include <JuceHeader.h>
#include "../../Visualizer/Analyser.h"

// ****************************************************************************
// SCALE Y CONTROLS CLASS
// ****************************************************************************
class ScaleYControls : public juce::Component
{
public:
    ScaleYControls( Analyser &a );
    ~ScaleYControls() override;
    
    
    // ========================================================================
    void paint( juce::Graphics &g ) override;
    void resized() override;

private:
    // ========================================================================
    Analyser &mr_analyser;
    
    juce::TextButton m_rangeTextButton;
    juce::Slider m_maximumVolumeSlider;
    juce::Slider m_minimumVolumeSlider;
    
    
    // ========================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR( ScaleYControls )
};
