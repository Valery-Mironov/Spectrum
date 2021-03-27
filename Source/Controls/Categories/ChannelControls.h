#pragma once

#include <JuceHeader.h>

// ****************************************************************************
// CHANNEL CONTROLS CLASS
// ****************************************************************************
class ChannelControls : public juce::Component
{
public:
    enum RadioButtonIds { channels = 1001 };
    
    
    // ========================================================================
    ChannelControls( juce::AudioProcessorValueTreeState & );
    ~ChannelControls() override;
    
    
    // ========================================================================
    void resized() override;

private:
    // ========================================================================
    juce::AudioProcessorValueTreeState &mr_audioProcessorValueTreeState;
    
    juce::TextButton m_leftChannelTextButton;
    juce::TextButton m_rightChannelTextButton;
    juce::TextButton m_bothChannelsTextButton;
    
    using Attachment = juce::AudioProcessorValueTreeState::ButtonAttachment;
    
    std::unique_ptr<Attachment> m_leftChannelTextButtonAttachment;
    std::unique_ptr<Attachment> m_rightChannelTextButtonAttachment;
    std::unique_ptr<Attachment> m_bothChannelsButtonAttachment;
    
    
    // ========================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR( ChannelControls )
};
