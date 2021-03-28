#include "Visualizer.h"

Visualizer::Visualizer(
    juce::AudioProcessorValueTreeState &audioProcessorValueTreeState,
    Analyser &analyser
) :
    m_grid( audioProcessorValueTreeState ),
    m_graph( audioProcessorValueTreeState, analyser )
{
    addAndMakeVisible( m_grid );
    m_grid.setGridColour( juce::Colour( 0xff464646 ) );
    m_grid.setTextColour( juce::Colour( 0xff848484 ) );
    
    addAndMakeVisible( m_graph );
    m_graph.setGraphColour( juce::Colour( 0xff48bde8 ) );
    m_graph.setGraphMaximumsColour( juce::Colour( 0xff245e74 ) );
}



Visualizer::~Visualizer() {}


// ============================================================================
void Visualizer::paint( juce::Graphics &g )
{
    juce::Path path;
    path.addRoundedRectangle( getLocalBounds(), m_marginInPixels );
    g.setColour( m_backgroundColour );
    g.fillPath( path );
}



void Visualizer::resized()
{
    auto area = getLocalBounds().reduced( m_marginInPixels );
    
    m_grid.setBounds( area );
    m_graph.setBounds( area );
}


// ============================================================================
void Visualizer::setBackgroundColour( juce::Colour colour )
{
    m_backgroundColour = colour;
}


// ========================================================================
void Visualizer::setMarginInPixels( const int margin )
{
    m_marginInPixels = margin;
}
