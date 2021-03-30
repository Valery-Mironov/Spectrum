#pragma once

#include <JuceHeader.h>

// ****************************************************************************
// GRAPH INFO LABEL CLASS
// ****************************************************************************
class GraphInfoLabel : public juce::Component
{
public:
    GraphInfoLabel( juce::AudioProcessorValueTreeState & );
    ~GraphInfoLabel() override;
    
    
    // ========================================================================
    void paint( juce::Graphics & ) override;
    void resized() override;
    
    
    // ========================================================================
    void setBackgroundColour( const juce::Colour & );
    void setColour( const juce::Colour & );
    
    
    // ========================================================================
    void setMarginInPixels( const int );
    
    
    // ========================================================================
    void setData( const float x, const float y, const bool isLogarithmic );

private:
    // ========================================================================
    int getFrequency( const float, const bool );
    juce::String getNote( const int );
    float getVolume( const float );
    
    
    // ========================================================================
    juce::AudioProcessorValueTreeState &mr_audioProcessorValueTreeState;
    
    juce::Rectangle<int> m_rectangle;
    
    static constexpr int m_width { 80 };
    static constexpr int m_height { 60 };
    
    juce::Label m_frequencyLabel;
    juce::Label m_noteLabel;
    juce::Label m_volumeLabel;
    
    
    juce::Colour m_backgroundColour { 0xff323232 };
    juce::Colour m_colour { 0xff48bde8 };
    
    int m_marginInPixels { 10 };
    
    
    // ========================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR( GraphInfoLabel )
};
