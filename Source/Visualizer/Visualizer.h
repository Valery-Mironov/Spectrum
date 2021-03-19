#pragma once

#include <JuceHeader.h>
#include "Layers/Grid.h"
#include "Layers/Graph.h"
#include "Analyser.h"

// ****************************************************************************
// VISUALISER CLASS
// ****************************************************************************
class Visualizer :
    public juce::Component
{
public:
    Visualizer( Analyser &a );
    ~Visualizer() override;
    
    
    // ========================================================================
    void paint( juce::Graphics &g ) override;
    void resized() override;
    
    
    // ========================================================================
    Graph &getReferenceToTheCurve();
    Grid &getReferenceToTheGrid();
    
private:
    // ========================================================================
    // Must be set by the 'set' method
    juce::Colour backgroundColour { 0xff323232 };
    // Must be set by the 'set' method
    static constexpr double m_marginInPixels { 10 };
    
    Grid m_grid;
    Graph m_graph;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR( Visualizer )
};
