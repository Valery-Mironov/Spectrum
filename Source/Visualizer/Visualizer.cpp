#include "Visualizer.h"

Visualizer::Visualizer( Analyser &a ) :
    // Min Hz, Max Hz, Min dB, Max dB
    m_grid( 24, 24000, -120, 12 ),
    m_graph( a )
{
    addAndMakeVisible( m_grid );
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


// ============================================================================
Graph &Visualizer::getReferenceToTheCurve()
{
    return m_graph;
}



Grid &Visualizer::getReferenceToTheGrid()
{
    return m_grid;
}
