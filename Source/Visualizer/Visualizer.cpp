#include "Visualizer.h"

Visualizer::Visualizer(
    juce::AudioProcessorValueTreeState &audioProcessorValueTreeState,
    Analyser &analyser ) :
        m_grid( audioProcessorValueTreeState ),
        m_graph( audioProcessorValueTreeState, analyser )
{
    addAndMakeVisible( m_grid );
    m_grid.setGridColour( juce::Colour( 0xff464646 ) );
    m_grid.setTextColour( juce::Colour( 0xff848484 ) );
    
    addAndMakeVisible( m_graph );
}



Visualizer::~Visualizer()
{
    
}


// ============================================================================
void Visualizer::paint( juce::Graphics &g )
{
    juce::Path path;
    path.addRoundedRectangle( getLocalBounds(), m_marginInPixels );
    g.setColour( backgroundColour );
    g.fillPath( path );
}



void Visualizer::resized()
{
    auto area = getLocalBounds().reduced( m_marginInPixels );
    
    m_grid.setBounds( area );
    m_graph.setBounds( area );
}
