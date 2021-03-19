#pragma once

#include <JuceHeader.h>

// ****************************************************************************
// AVG CONTROL CLASS
// ****************************************************************************
class AvgControl : public juce::Component
{
public:
    AvgControl();
    ~AvgControl() override;
    
    
    // ========================================================================
    void paint( juce::Graphics &g ) override;
    void resized() override;

private:
    // ========================================================================
    juce::Slider m_avgSlider;
    
    
    // ========================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR( AvgControl )
};
