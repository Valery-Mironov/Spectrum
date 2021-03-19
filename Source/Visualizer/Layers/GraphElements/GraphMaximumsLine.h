#pragma once

#include <JuceHeader.h>
#include "GraphLine.h"
#include "../../Analyser.h"

// ****************************************************************************
// GRAPH MAXIMUMS LINE CLASS
// ****************************************************************************
class GraphMaximumsLine : public GraphLine
{
public:
    GraphMaximumsLine( Analyser &analyser );
    ~GraphMaximumsLine() override;
    
private:
    // ========================================================================
    float getScopeDataFromAnalyser( size_t index ) override;
    
    
    // ========================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR( GraphMaximumsLine )
};
