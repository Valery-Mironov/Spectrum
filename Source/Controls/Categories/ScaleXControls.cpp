#include "ScaleXControls.h"

ScaleXControls::ScaleXControls(
    juce::AudioProcessorValueTreeState &audioProcessorValueTreeState
) : mr_audioProcessorValueTreeState( audioProcessorValueTreeState )
{
    addAndMakeVisible( m_linearModeTextButton );
    m_linearModeTextButton.setButtonText( "Lin" );
    m_linearModeTextButton.setClickingTogglesState( true );
    m_linearModeTextButton.setRadioGroupId( scale );
    
    m_linTextButtonAttachment =
        std::make_unique<Attachment>(
            mr_audioProcessorValueTreeState,
            "LIN_ID",
            m_linearModeTextButton
        );
    
    addAndMakeVisible( m_logarithmicModeTextButton );
    m_logarithmicModeTextButton.setButtonText( "Log" );
    m_logarithmicModeTextButton.setClickingTogglesState( true );
    m_logarithmicModeTextButton.setRadioGroupId( scale );
    m_logarithmicModeTextButton.setToggleState( true, juce::dontSendNotification );
    
    m_logTextButtonAttachment =
        std::make_unique<Attachment>(
            mr_audioProcessorValueTreeState,
            "LOG_ID",
            m_logarithmicModeTextButton
        );
    
    addAndMakeVisible( m_stModeTextButton );
    m_stModeTextButton.setButtonText( "ST" );
    m_stModeTextButton.setClickingTogglesState( true );
    m_stModeTextButton.setRadioGroupId( scale );
    
    m_stTextButtonAttachment =
        std::make_unique<Attachment>(
            mr_audioProcessorValueTreeState,
            "ST_ID",
            m_stModeTextButton
        );
}



ScaleXControls::~ScaleXControls() {}


// ============================================================================
void ScaleXControls::resized()
{
    auto indent { 3 };
    auto area { getLocalBounds() };
    auto buttonWidth
    {
        ( area.getWidth() - indent * 2 ) / 3
    };
    
    m_linearModeTextButton.setBounds( area.removeFromLeft( buttonWidth ) );
    area.removeFromLeft( indent );
    
    m_stModeTextButton.setBounds( area.removeFromRight( buttonWidth ) );
    area.removeFromRight( indent );
    
    m_logarithmicModeTextButton.setBounds( area );
}
