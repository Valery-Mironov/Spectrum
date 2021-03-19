#include "ChannelControls.h"

ChannelControls::ChannelControls( Analyser &a ) : mr_analyser( a )
{
    addAndMakeVisible( m_leftTextButton );
    m_leftTextButton.setButtonText( "L" );
    m_leftTextButton.setClickingTogglesState( true );
    m_leftTextButton.setRadioGroupId( e_ChannelsButtons );
    m_leftTextButton.onClick = [ this ]
    {
        mr_analyser.setChannels( e_Left );
    };

    addAndMakeVisible( m_rightTextButton );
    m_rightTextButton.setButtonText( "R" );
    m_rightTextButton.setClickingTogglesState( true );
    m_rightTextButton.setRadioGroupId( e_ChannelsButtons );
    m_rightTextButton.onClick = [ this ]
    {
        mr_analyser.setChannels( e_Right );
    };
    
    addAndMakeVisible( m_leftPlusRightTextButton );
    m_leftPlusRightTextButton.setButtonText( "L + R" );
    m_leftPlusRightTextButton.setClickingTogglesState( true );
    m_leftPlusRightTextButton.setRadioGroupId( e_ChannelsButtons );
    m_leftPlusRightTextButton.onClick = [ this ]
    {
        mr_analyser.setChannels( e_LeftPlusRight );
    };
    m_leftPlusRightTextButton.setToggleState(
        true,
        juce::dontSendNotification );
}



ChannelControls::~ChannelControls()
{
    
}


// ============================================================================
void ChannelControls::paint( juce::Graphics &g )
{
    
}



void ChannelControls::resized()
{
    auto indent { 3 };
    auto area { getLocalBounds() };
    auto buttonWidth
    {
        ( area.getWidth() - indent * 2 ) / 3
    };
    
    m_leftTextButton.setBounds( area.removeFromLeft( buttonWidth ) );
    area.removeFromLeft( indent );
    
    m_leftPlusRightTextButton.setBounds( area.removeFromRight( buttonWidth ) );
    area.removeFromRight( indent );
    
    m_rightTextButton.setBounds( area );
}
