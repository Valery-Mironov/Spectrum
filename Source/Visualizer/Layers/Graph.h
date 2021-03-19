#pragma once

#include <JuceHeader.h>
#include "../Analyser.h"
#include "GraphElements/GraphLine.h"
#include "GraphElements/GraphBins.h"
#include "GraphElements/GraphMaximumsLine.h"

/*
    TASKS
    
    Layer with interpretation of cursor position in note, frequency and volume
    Make the maximum and minimum values invisible
*/

// ****************************************************************************
// GRAPH CLASS
// ****************************************************************************
class Graph :
    public juce::Component,
    private juce::Timer
{
public:
    Graph( Analyser &analyser );
    ~Graph() override;
    
    
    // ========================================================================
    void paint( juce::Graphics &g ) override;
    void resized() override;
    
    
    // ========================================================================
    void mouseDown( const juce::MouseEvent &event ) override;
    
    
    // ========================================================================
    void setTimerInterval( int milliseconds );
    void timerCallback() override;
    
    
    // ========================================================================
    void setScaleType( bool isLogarithmic );
    void setGraphStyleAsBins( bool isBins );
    void maximumVolumesAreShown( bool areShown );
    
private:
    // ========================================================================
    Analyser &mr_analyser;
    
    GraphMaximumsLine m_graphMaximumsLine;
    GraphLine m_graphLine;
    GraphBins m_graphBins;
    
    
    // ========================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR( Graph )
};
