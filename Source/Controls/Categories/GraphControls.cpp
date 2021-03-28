#include "GraphControls.h"

GraphControls::GraphControls(
    juce::AudioProcessorValueTreeState &audioProcessorValueTreeState
) :
    mr_audioProcessorValueTreeState( audioProcessorValueTreeState )
{
    addAndMakeVisible( m_lineTextButton );
    m_lineTextButton.setButtonText( "Line" );
    m_lineTextButton.setClickingTogglesState( true );
    m_lineTextButton.onClick = [ this ]
    {
        if ( m_lineTextButton.getToggleState() == true )
        {
            m_lineTextButton.setButtonText( "Line" );
        }
        else
        {
            m_lineTextButton.setButtonText( "Bins" );
        }
    };
    
    m_lineTextButtonAttachment =
        std::make_unique<Attachment>(
            mr_audioProcessorValueTreeState,
            "BINS_ID",
            m_lineTextButton
        );
    
    addAndMakeVisible( m_maxTextButton );
    m_maxTextButton.setButtonText( "Max" );
    m_maxTextButton.setClickingTogglesState( true );
    
    m_maxTextButtonAttachment =
        std::make_unique<Attachment>(
            mr_audioProcessorValueTreeState,
            "MAX_ID",
            m_maxTextButton
        );
}



GraphControls::~GraphControls() {}


// ============================================================================
void GraphControls::resized()
{
    auto indent { 3 };
    auto area { getLocalBounds() };
    auto buttonWidth
    {
        ( area.getWidth() - indent ) / 2
    };
    
    m_lineTextButton.setBounds( area.removeFromLeft( buttonWidth ) );
    m_maxTextButton.setBounds( area.removeFromRight( buttonWidth ) );
}
