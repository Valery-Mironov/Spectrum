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
    Visualizer( juce::AudioProcessorValueTreeState &, Analyser & );
    ~Visualizer() override;
    
    
    // ========================================================================
    void paint( juce::Graphics & ) override;
    void resized() override;
    
private:
    // ========================================================================
    Grid m_grid;
    Graph m_graph;
    
    // Must be set by the 'set' method
    juce::Colour backgroundColour { 0xff323232 };
    // Must be set by the 'set' method
    static constexpr double m_marginInPixels { 10 };
    
    
    // ========================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR( Visualizer )
};
