#pragma once

#include <JuceHeader.h>
#include "GraphLine.h"

// ****************************************************************************
// GRAPH BINS CLASS
// ****************************************************************************
class GraphBins : public GraphLine
{
public:
    GraphBins( Analyser &analyser );
    ~GraphBins();
    
private:
    // ========================================================================
    void drawFrame( juce::Graphics &g ) override;
    
    
    // ========================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR( GraphBins )
};
