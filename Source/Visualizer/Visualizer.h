#pragma once

#include <JuceHeader.h>
#include "Layers/Grid.h"
#include "Layers/Graph.h"
#include "Analyser.h"

/*
    TASKS
    
    Layer with interpretation of cursor position in note, frequency and volume.
*/

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
    
    
    // ========================================================================
    void setBackgroundColour( const juce::Colour & );
    
    
    // ========================================================================
    void setMarginInPixels( const int );
    
private:
    // ========================================================================
    Grid m_grid;
    Graph m_graph;
    
    juce::Colour m_backgroundColour { 0xff323232 };
    int m_marginInPixels { 10 };
    
    
    // ========================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR( Visualizer )
};
