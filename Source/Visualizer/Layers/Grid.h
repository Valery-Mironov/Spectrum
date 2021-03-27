#pragma once

#include <JuceHeader.h>
#include "GridElements/LogarithmicScale.h"
#include "GridElements/LinearScale.h"
#include "GridElements/NoteScale.h"

// ****************************************************************************
// GRID CLASS
// ****************************************************************************
class Grid :
    public juce::Component,
    public juce::AudioProcessorValueTreeState::Listener
{
public:
    enum class GridStyles { linear, logarithmic, st };
    
    
    // =======================================================================
    Grid( juce::AudioProcessorValueTreeState & );
    ~Grid() override;
    
    
    // ========================================================================
    void paint( juce::Graphics & ) override;
    void resized() override;
    
    
    // ========================================================================
    void setGridColour( juce::Colour );
    void setTextColour( juce::Colour );
    
private:
    // ========================================================================
    void parameterChanged( const juce::String &, float ) override;
    
    
    // ========================================================================
    void setGridStyle( GridStyles );
    void setVolumeRangeInDecibels( int, int );
    void calculateAmplitudeGrid();
    void addLabels();
    
    
    // ========================================================================
    juce::AudioProcessorValueTreeState &mr_audioProcessorValueTreeState;
    
    bool m_gridStyleIsLinear { false };
    bool m_gridStyleIsLogarithmic { true };
    bool m_gridStyleIsST { false };
    
    LogarithmicScale m_logarithmicScale;
    LinearScale m_linearScale;
    NoteScale m_noteScale;
    
    juce::Colour m_gridColour { 0xff464646 };
    juce::Colour m_textColour { 0xff848484 };
    
    std::atomic<int> m_maximumVolumeInDecibels { 12 };
    std::atomic<int> m_minimumVolumeInDecibels { -120 };
    std::atomic<int> m_firstOffsetInDecibels;
    std::atomic<int> m_offsetInDecibels;
    
    std::vector<float> m_volumeGridPoints;
    std::map<int, std::unique_ptr<juce::Label>> m_labels;
    
    
    // ========================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR( Grid )
};
