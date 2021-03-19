#pragma once

#include <JuceHeader.h>
#include "../../Visualizer/Analyser.h"

// ****************************************************************************
// CHANNEL CONTROLS CLASS
// ****************************************************************************
class ChannelControls : public juce::Component
{
public:
    enum RadioButtonIds
    {
        e_ChannelsButtons = 1001
    };
    
    
    
    enum SelectedChannels
    {
        e_Left,
        e_Right,
        e_LeftPlusRight
    };
    
    
    // ========================================================================
    ChannelControls( Analyser &a );
    ~ChannelControls() override;
    
    
    // ========================================================================
    void paint( juce::Graphics &g ) override;
    void resized() override;

private:
    // ========================================================================
    Analyser &mr_analyser;
    
    juce::TextButton m_leftTextButton;
    juce::TextButton m_rightTextButton;
    juce::TextButton m_leftPlusRightTextButton;
    
    
    // ========================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR( ChannelControls )
};
