#include "Visualizer.h"

// ****************************************************************************
// VISUALISER CLASS
// ****************************************************************************
Visualizer::Visualizer( Analyser &a ) :
    // Min Hz, Max Hz, Min dB, Max dB
    m_grid( 24, 24000, -120, 12 ),
    m_curve( a )
{
    addAndMakeVisible( m_grid );
    addAndMakeVisible( m_curve );
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
    m_curve.setBounds( area );
}
