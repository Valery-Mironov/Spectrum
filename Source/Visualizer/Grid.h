#pragma once

#include <JuceHeader.h>

// ****************************************************************************
// GRID CLASS
// ****************************************************************************
class Grid : public juce::Component
{
public:
    Grid(
        const int minimumFrequencyInHertz,
        const int maximumFrequencyInHertz,
        const int minimumVolumeInDecibels,
        const int maximumVolumeInDecibels );
    ~Grid() override;
    
    
    // ========================================================================
    void paint( juce::Graphics &g ) override;
    void resized() override;
    
private:
    // ========================================================================
    int getOffsetInHertz(
        const int currentFrequencyInHertz );
    int getCurrentFrequencyInHertz(
        const int currentFrequencyInHertz,
        const int offsetInHertz );
    
    
    // ========================================================================
    void calculateBaseTenLogarithm(
        const int minimumFrequencyInHertz,
        const int maximumFrequencyInHertz );
    void calculateFrequencyGrid();
    void calculateAmplitudeGrid(
        const int miniumInDecibels,
        const int maximumInDecibels );
    void addLabels();
    
    
    
    // ========================================================================
    // Must be set by the 'set' method
    juce::Colour m_gridColour { 0xff848484 };
    // Should be calculated automatically
    static constexpr int m_stepInDecibels { 12 };
    static constexpr int m_coefficient { 10 };
    
    const int m_maximumVolumeInDecibels;
    const int m_minimumVolumeInDecibels;
    
    // Possible to convert to 'map'
    std::vector<int> m_volumeGridPoints;
    std::map<int, float> m_baseTenLogarithm;
    std::map<int, float> m_frequencyGridPoints;
    std::map<int, std::unique_ptr<juce::Label>> m_labels;
    
    
    // ========================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR( Grid )
};
