#pragma once

#include <JuceHeader.h>

// ****************************************************************************
// LINEAR SCALE CLASS
// ****************************************************************************
class LinearScale : public juce::Component
{
public:
    LinearScale();
    ~LinearScale() override;
    
    
    // ========================================================================
    void paint( juce::Graphics & ) override;
    void resized() override;
    
    
    // ========================================================================
    void setGridColour( juce::Colour );
    void setTextColour( juce::Colour );
    
    
private:
    // ========================================================================
    void calculateFrequencyGrid();
    void addLabels();
    
    
    // ========================================================================
    juce::Colour m_gridColour { 0xff464646 };
    juce::Colour m_textColour { 0xff848484 };
    
    static constexpr int m_kilohertz { 1000 };
    static constexpr int m_maximumFrequencyInHertz { 24000 };
    static constexpr int m_minimumFrequencyInHertz { 24 };
    
    std::map<int, float> m_frequencyGridPoints;
    std::map<int, std::unique_ptr<juce::Label>> m_labels;
    
    
    // ========================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR( LinearScale )
};
