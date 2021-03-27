#pragma once

#include <JuceHeader.h>

// ****************************************************************************
// AVG CONTROL CLASS
// ****************************************************************************
class AvgControl : public juce::Component
{
public:
    AvgControl( juce::AudioProcessorValueTreeState & );
    ~AvgControl() override;
    
    
    // ========================================================================
    void resized() override;

private:
    // ========================================================================
    juce::AudioProcessorValueTreeState &mr_audioProcessorValueTreeState;
    juce::Slider m_avgSlider;
    
    using Attachment = juce::AudioProcessorValueTreeState::SliderAttachment;
    std::unique_ptr<Attachment> m_avgSliderAttachment;
    
    
    // ========================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR( AvgControl )
};
