#pragma once

#include <JuceHeader.h>
#include "GraphLine.h"

// ****************************************************************************
// GRAPH BINS CLASS
// ****************************************************************************
class GraphBins : public GraphLine
{
public:
    GraphBins( Analyser & );
    ~GraphBins();
    
private:
    // ========================================================================
    void drawFrame( juce::Graphics & ) override;
    
    
    // ========================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR( GraphBins )
};
