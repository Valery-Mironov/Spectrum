#include "ChannelControls.h"

ChannelControls::ChannelControls(
    juce::AudioProcessorValueTreeState &audioProcessorValueTreeState
) :
    mr_audioProcessorValueTreeState( audioProcessorValueTreeState )
{    
    addAndMakeVisible( m_leftChannelTextButton );
    m_leftChannelTextButton.setButtonText( "Left" );
    m_leftChannelTextButton.setClickingTogglesState( true );
    m_leftChannelTextButton.setRadioGroupId( channels );
    
    m_leftChannelTextButtonAttachment =
        std::make_unique<Attachment>(
            mr_audioProcessorValueTreeState,
            "LEFT_ID",
            m_leftChannelTextButton
        );
    
    addAndMakeVisible( m_rightChannelTextButton );
    m_rightChannelTextButton.setButtonText( "Right" );
    m_rightChannelTextButton.setClickingTogglesState( true );
    m_rightChannelTextButton.setRadioGroupId( channels );
    
    m_rightChannelTextButtonAttachment =
        std::make_unique<Attachment>(
            mr_audioProcessorValueTreeState,
            "RIGHT_ID",
            m_rightChannelTextButton
        );
    
    addAndMakeVisible( m_bothChannelsTextButton );
    m_bothChannelsTextButton.setButtonText( "Both" );
    m_bothChannelsTextButton.setClickingTogglesState( true );
    m_bothChannelsTextButton.setRadioGroupId( channels );
    
    m_bothChannelsButtonAttachment =
        std::make_unique<Attachment>(
            mr_audioProcessorValueTreeState,
            "BOTH_ID",
            m_bothChannelsTextButton
        );
}



ChannelControls::~ChannelControls() {}


// ============================================================================
void ChannelControls::resized()
{
    auto indent { 3 };
    auto area { getLocalBounds() };
    auto buttonWidth { ( area.getWidth() - indent * 2 ) / 3 };
    
    m_leftChannelTextButton.setBounds( area.removeFromLeft( buttonWidth ) );
    area.removeFromLeft( indent );
    
    m_bothChannelsTextButton.setBounds( area.removeFromRight( buttonWidth ) );
    area.removeFromRight( indent );
    
    m_rightChannelTextButton.setBounds( area );
}
