#pragma once

#include <JuceHeader.h>
#include "../../Visualizer/Layers/Graph.h"

// ****************************************************************************
// REFRESH CONTROL CLASS
// ****************************************************************************
class RefreshControl : public juce::Component
{
public:
    RefreshControl( Graph &c );
    ~RefreshControl() override;
    
    
    // ========================================================================
    void paint( juce::Graphics &g ) override;
    void resized() override;

private:
    // ========================================================================
    Graph &mr_curve;
    
    juce::Slider m_refreshSlider;
    
    
    // ========================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR( RefreshControl )
};
