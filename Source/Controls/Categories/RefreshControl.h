#pragma once

#include <JuceHeader.h>

// ****************************************************************************
// REFRESH CONTROL CLASS
// ****************************************************************************
class RefreshControl : public juce::Component
{
public:
    RefreshControl( juce::AudioProcessorValueTreeState & );
    ~RefreshControl() override;
    
    
    // ========================================================================
    void resized() override;

private:
    // ========================================================================
    juce::AudioProcessorValueTreeState &mr_audioProcessorValueTreeState;
    juce::Slider m_refreshSlider;
    
    using Attachment = juce::AudioProcessorValueTreeState::SliderAttachment;
    std::unique_ptr<Attachment> m_refreshSliderAttachment;
    
    
    // ========================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR( RefreshControl )
};
