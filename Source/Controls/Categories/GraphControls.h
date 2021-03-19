#pragma once

#include <JuceHeader.h>
#include "../../Visualizer/Layers/Graph.h"

// ****************************************************************************
// GRAPH CONTROLS CLASS
// ****************************************************************************
class GraphControls : public juce::Component
{
public:
    GraphControls( Graph &c );
    ~GraphControls() override;
    
    
    // ========================================================================
    void paint( juce::Graphics &g ) override;
    void resized() override;

private:
    // ========================================================================
    Graph &mr_curve;
    
    juce::TextButton m_lineTextButon;
    juce::TextButton m_maxTextButton;
    
    
    // ========================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR( GraphControls )
};
