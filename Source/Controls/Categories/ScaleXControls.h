#pragma once

#include <JuceHeader.h>

// ****************************************************************************
// SCALE X CONTROLS CLASS
// ****************************************************************************
class ScaleXControls : public juce::Component
{
public:
    enum RadioButtonIds { scale = 1002 };
    
    
    // ========================================================================
    ScaleXControls( juce::AudioProcessorValueTreeState & );
    ~ScaleXControls() override;
    
    
    // ========================================================================
    void resized() override;

private:
    // ========================================================================
    juce::AudioProcessorValueTreeState &mr_audioProcessorValueTreeState;
    
    juce::TextButton m_linearModeTextButton;
    juce::TextButton m_logarithmicModeTextButton;
    juce::TextButton m_stModeTextButton;
    
    using Attachment = juce::AudioProcessorValueTreeState::ButtonAttachment;
    std::unique_ptr<Attachment> m_linTextButtonAttachment;
    std::unique_ptr<Attachment> m_logTextButtonAttachment;
    std::unique_ptr<Attachment> m_stTextButtonAttachment;
    
    
    // ========================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR( ScaleXControls )
};
