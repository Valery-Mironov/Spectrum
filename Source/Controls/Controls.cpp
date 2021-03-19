#include "Controls.h"

Controls::Controls( Analyser &analyser, Graph &graph, Grid &grid ) :
    m_blockControl( analyser ),
    m_channelControls( analyser ),
    m_refreshControl( graph ),
    m_graphControls( graph ),
    m_scaleXControls( graph, grid ),
    m_scaleYControls( analyser )
{
    addAndMakeVisible( m_blockLabel );
    m_blockLabel.setText( "Block", juce::dontSendNotification );
    m_blockLabel.attachToComponent( &m_blockControl, true );
    addAndMakeVisible( m_blockControl );
    
    addAndMakeVisible( m_channelLabel );
    m_channelLabel.setText( "Channel", juce::dontSendNotification );
    m_channelLabel.attachToComponent( &m_channelControls, true );
    addAndMakeVisible( m_channelControls );
    
    addAndMakeVisible( m_refreshLabel );
    m_refreshLabel.setText( "Refresh", juce::dontSendNotification );
    m_refreshLabel.attachToComponent( &m_refreshControl, true );
    addAndMakeVisible( m_refreshControl );
    
    addAndMakeVisible( m_avgLabel );
    m_avgLabel.setText( "Avg", juce::dontSendNotification );
    m_avgLabel.attachToComponent( &m_avgControl, true );
    addAndMakeVisible( m_avgControl );
    
    addAndMakeVisible( m_graphLabel );
    m_graphLabel.setText( "Graph", juce::dontSendNotification );
    m_graphLabel.attachToComponent( &m_graphControls, true );
    addAndMakeVisible( m_graphControls );
    
    addAndMakeVisible( m_scaleLabel );
    m_scaleLabel.setText( "Scale X", juce::dontSendNotification );
    m_scaleLabel.attachToComponent( &m_scaleXControls, true );
    addAndMakeVisible( m_scaleXControls );
    
    addAndMakeVisible( m_scaleYControls );
}



Controls::~Controls()
{
    
}


// ============================================================================
void Controls::paint( juce::Graphics &g )
{
    
}



void Controls::resized()
{
    auto itemHeight { 20 };
    auto area { getLocalBounds() };
    
    area.reduced( m_marginInPixels );
    area.removeFromLeft( getHeight() / 3 );
        
    m_blockControl.setBounds( area.removeFromTop( itemHeight ) );
    m_channelControls.setBounds( area.removeFromTop( itemHeight ) );
    m_refreshControl.setBounds( area.removeFromTop( itemHeight ) );
    m_avgControl.setBounds( area.removeFromTop( itemHeight ) );
    m_graphControls.setBounds( area.removeFromTop( itemHeight ) );
    m_scaleXControls.setBounds( area.removeFromTop( itemHeight ) );
    m_scaleYControls.setBounds( area.removeFromTop( itemHeight ) );
}
