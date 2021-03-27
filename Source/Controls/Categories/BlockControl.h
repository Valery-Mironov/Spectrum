#pragma once

#include <JuceHeader.h>

// ****************************************************************************
// BLOCK CONTROL CLASS
// ****************************************************************************
class BlockControl : public juce::Component
{
public:
    BlockControl( juce::AudioProcessorValueTreeState & );
    ~BlockControl() override;
    
    
    // ========================================================================
    void resized() override;

private:
    // ========================================================================
    juce::AudioProcessorValueTreeState &mr_audioProcessorValueTreeState;
    juce::ComboBox m_blockComboBox;
    
    using Attachment = juce::AudioProcessorValueTreeState::ComboBoxAttachment;
    std::unique_ptr<Attachment> m_blockComboBoxAttachment;
    
    
    // ========================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR( BlockControl )
};
