#include "ScaleXControls.h"

ScaleXControls::ScaleXControls( Graph &graph, Grid &grid) :
    mr_graph( graph ),
    mr_grid( grid )
{
    addAndMakeVisible( m_linTextButton );
    m_linTextButton.setButtonText( "Lin" );
    m_linTextButton.setClickingTogglesState( true );
    m_linTextButton.setRadioGroupId( e_ScaleTypeButtons );
    m_linTextButton.onClick = [ this ] { mr_graph.setScaleType( false ); };
    
    addAndMakeVisible( m_logTextButton );
    m_logTextButton.setButtonText( "Log" );
    m_logTextButton.setClickingTogglesState( true );
    m_logTextButton.setRadioGroupId( e_ScaleTypeButtons );
    m_logTextButton.onClick = [ this ] { mr_graph.setScaleType( true ); };
    m_logTextButton.setToggleState( true, juce::dontSendNotification );
    
    addAndMakeVisible( m_stTextButton );
    m_stTextButton.setButtonText( "ST" );
    m_stTextButton.setClickingTogglesState( true );
    m_stTextButton.setRadioGroupId( e_ScaleTypeButtons );
    m_logTextButton.onClick = [ this ] { mr_graph.setScaleType( true ); };
}



ScaleXControls::~ScaleXControls()
{
    
}


// ============================================================================
void ScaleXControls::paint( juce::Graphics &g )
{
    
}



void ScaleXControls::resized()
{
    auto indent { 3 };
    auto area { getLocalBounds() };
    auto buttonWidth
    {
        ( area.getWidth() - indent * 2 ) / 3
    };
    
    m_linTextButton.setBounds( area.removeFromLeft( buttonWidth ) );
    area.removeFromLeft( indent );
    
    m_stTextButton.setBounds( area.removeFromRight( buttonWidth ) );
    area.removeFromRight( indent );
    
    m_logTextButton.setBounds( area );
}
