#pragma once

#include <JuceHeader.h>
#include "../Analyser.h"
#include "GraphElements/GraphLine.h"
#include "GraphElements/GraphBins.h"
#include "GraphElements/GraphMaximumsLine.h"

/*
    TASKS
    
    Layer with interpretation of cursor position in note, frequency and volume
*/

// ****************************************************************************
// GRAPH CLASS
// ****************************************************************************
class Graph :
    public juce::Component,
    public juce::AudioProcessorValueTreeState::Listener,
    private juce::Timer
{
public:
    Graph( juce::AudioProcessorValueTreeState &, Analyser & );
    ~Graph() override;
    
    
    // ========================================================================
    void paint( juce::Graphics & ) override;
    void resized() override;
    
    
    // ========================================================================
    void mouseDown( const juce::MouseEvent & ) override;
    
    
    // ========================================================================
    void timerCallback() override;
    
private:
    // ========================================================================
    void setTimerInterval( int );
    void setGraphStyleAsLine( bool );
    void setMaximumVolumesVisible( bool );
    void setScaleTypeAsLogarithmic( bool );
    
    
    // ========================================================================
    void parameterChanged( const juce::String &, float ) override;
    
    
    // ========================================================================
    juce::AudioProcessorValueTreeState &mr_audioProcessorValueTreeState;
    Analyser &mr_analyser;
    
    GraphMaximumsLine m_graphMaximumsLine;
    GraphLine m_graphLine;
    GraphBins m_graphBins;
    
    std::atomic<bool> m_graphStyleIsLine { true };
    std::atomic<bool> m_maximumVolumesIsVisible { true };
    std::atomic<bool> m_scaleTypeIsLogarithmic { true };
    
    juce::Colour m_volumeMaximumsGraphColour { 0xff245e74 };
    juce::Colour m_volumeGraphColour { 0xff48bde8 };
    
    
    // ========================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR( Graph )
};
