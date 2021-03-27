#pragma once

#include <JuceHeader.h>

// ****************************************************************************
// NOTE SCALE CLASS
// ****************************************************************************
class NoteScale : public juce::Component
{
public:
    NoteScale();
    ~NoteScale() override;
    
    
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
    juce::Colour m_gridColour { 0xff464646 };
    juce::Colour m_textColour { 0xff848484 };
    
    std::map<int, float> m_baseTenLogarithm;
    std::map<int, float> m_noteGridPoints;
    std::map<int, std::unique_ptr<juce::Label>> m_labels;
    
    int m_firstNote { 0 };
    int m_lastNote { 112 };
    
    // ========================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR( NoteScale )
};
