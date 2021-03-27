#pragma once

#include <JuceHeader.h>

// ****************************************************************************
// SCALE Y CONTROLS CLASS
// ****************************************************************************
class ScaleYControls : public juce::Component
{
public:
    ScaleYControls( juce::AudioProcessorValueTreeState & );
    ~ScaleYControls() override;
    
    
    // ========================================================================
    void resized() override;

private:
    // ========================================================================
    juce::AudioProcessorValueTreeState &mr_audioProcessorValueTreeState;
    
    juce::TextButton m_rangeModeTextButton;
    juce::Slider m_maximumVolumeSlider;
    juce::Slider m_minimumVolumeSlider;
    
    using ButtonAttachment = juce::AudioProcessorValueTreeState::ButtonAttachment;
    std::unique_ptr<ButtonAttachment> m_rangeTextButtonAttachment;
    
    using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;
    std::unique_ptr<SliderAttachment> m_maximumVolumeSliderAttachment;
    std::unique_ptr<SliderAttachment> m_minimumVolumeSliderAttachment;
    
    
    // ========================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR( ScaleYControls )
};
