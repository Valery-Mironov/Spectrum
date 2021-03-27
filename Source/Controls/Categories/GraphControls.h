#pragma once

#include <JuceHeader.h>

// ****************************************************************************
// GRAPH CONTROLS CLASS
// ****************************************************************************
class GraphControls : public juce::Component
{
public:
    GraphControls( juce::AudioProcessorValueTreeState & );
    ~GraphControls() override;
    
    
    // ========================================================================
    void resized() override;

private:
    // ========================================================================
    juce::AudioProcessorValueTreeState &mr_audioProcessorValueTreeState;
    
    juce::TextButton m_lineTextButton;
    juce::TextButton m_maxTextButton;
    
    using Attachment = juce::AudioProcessorValueTreeState::ButtonAttachment;
    std::unique_ptr<Attachment> m_lineTextButtonAttachment;
    std::unique_ptr<Attachment> m_maxTextButtonAttachment;
    
    
    // ========================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR( GraphControls )
};
