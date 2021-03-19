#pragma once

#include <JuceHeader.h>
#include "../../Visualizer/Layers/Graph.h"
#include "../../Visualizer/Layers/Grid.h"

// ****************************************************************************
// SCALE X CONTROLS CLASS
// ****************************************************************************
class ScaleXControls : public juce::Component
{
public:
    enum RadioButtonIds
    {
        e_ScaleTypeButtons = 1002
    };
    
    
    // ========================================================================
    ScaleXControls( Graph &c, Grid &g );
    ~ScaleXControls() override;
    
    
    // ========================================================================
    void paint( juce::Graphics &g ) override;
    void resized() override;

private:
    // ========================================================================
    Graph &mr_graph;
    Grid &mr_grid;
    
    juce::TextButton m_linTextButton;
    juce::TextButton m_logTextButton;
    juce::TextButton m_stTextButton;
    
    
    // ========================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR( ScaleXControls )
};
