#include "GraphControls.h"

GraphControls::GraphControls( Graph &c ) : mr_curve( c )
{
    addAndMakeVisible( m_lineTextButon );
    m_lineTextButon.setButtonText( "Line" );
    m_lineTextButon.setClickingTogglesState( true );
    m_lineTextButon.setToggleState(
        false,
        juce::dontSendNotification );
    m_lineTextButon.onClick = [ this ]
    {
        if ( m_lineTextButon.getToggleState() == true )
        {
            m_lineTextButon.setButtonText( "Bins" );
            mr_curve.setGraphStyleAsBins( true );
        }
        else
        {
            m_lineTextButon.setButtonText( "Line" );
            mr_curve.setGraphStyleAsBins( false );
        }
    };
    
    addAndMakeVisible( m_maxTextButton );
    m_maxTextButton.setButtonText( "Max" );
    m_maxTextButton.setClickingTogglesState( true );
    m_maxTextButton.setToggleState(
        true,
        juce::dontSendNotification );
    m_maxTextButton.onClick = [ this ]
    {
        if ( m_maxTextButton.getToggleState() == true )
        {
            mr_curve.maximumVolumesAreShown( true );
        }
        else
        {
            mr_curve.maximumVolumesAreShown( false );
        }
    };
}



GraphControls::~GraphControls()
{
    
}


// ============================================================================
void GraphControls::paint( juce::Graphics &g )
{
    
}



void GraphControls::resized()
{
    auto indent { 3 };
    auto area { getLocalBounds() };
    auto buttonWidth
    {
        ( area.getWidth() - indent ) / 2
    };
    
    m_lineTextButon.setBounds( area.removeFromLeft( buttonWidth ) );
    m_maxTextButton.setBounds( area.removeFromRight( buttonWidth ) );
}
