#pragma once

#include <JuceHeader.h>

// ****************************************************************************
// LOGARITHMIC SCALE CLASS
// ****************************************************************************
class LogarithmicScale : public juce::Component
{
public:
    LogarithmicScale();
    ~LogarithmicScale() override;
    
    
    // ========================================================================
    void paint( juce::Graphics & ) override;
    void resized() override;
    
    
    // ========================================================================
    void setGridColour( juce::Colour );
    void setTextColour( juce::Colour );
    
    
private:
    // ========================================================================
    void calculateBaseTenLogarithm();
    void calculateFrequencyGrid();
    void addLabels();
    
    
    // ========================================================================
    int getOffsetInHertz( const int );
    int getCurrentFrequencyInHertz( const int, const int );
    
    
    // ========================================================================
    juce::Colour m_gridColour { 0xff464646 };
    juce::Colour m_textColour { 0xff848484 };
    
    static constexpr int m_coefficient { 10 };
    static constexpr int m_maximumFrequencyInHertz { 24000 };
    static constexpr int m_minimumFrequencyInHertz { 24 };
    
    std::map<int, float> m_baseTenLogarithm;
    std::map<int, float> m_noteGridPoints;
    std::map<int, std::unique_ptr<juce::Label>> m_labels;
    
    
    // ========================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR( LogarithmicScale )
};
