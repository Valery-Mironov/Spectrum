#pragma once

#include <JuceHeader.h>
#include "../Analyser.h"
#include "GraphElements/GraphLine.h"
#include "GraphElements/GraphBins.h"
#include "GraphElements/GraphMaximumsLine.h"

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
    
    
    // ========================================================================
    void setGraphColour( juce::Colour );
    void setGraphMaximumsColour( juce::Colour );
    
private:
    // ========================================================================
    void setTimerInterval( const int );
    void setGraphStyleAsLine( const bool );
    void setMaximumVolumesVisible( const bool );
    void setScaleTypeAsLogarithmic( const bool );
    
    
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
    
    juce::Colour m_volumeGraphColour { 0xff48bde8 };
    juce::Colour m_volumeMaximumsGraphColour { 0xff245e74 };
    
    
    // ========================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR( Graph )
};
