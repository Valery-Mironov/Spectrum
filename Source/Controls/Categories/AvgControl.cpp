#include "AvgControl.h"

// ****************************************************************************
// AVG CONTROL CLASS
// ****************************************************************************
AvgControl::AvgControl()
{
    addAndMakeVisible( m_avgSlider );
    m_avgSlider.setSliderStyle(
        juce::Slider::SliderStyle::LinearBar );
    m_avgSlider.setRange( 1, 8, 1 );
    m_avgSlider.setValue( 1, juce::dontSendNotification );
    m_avgSlider.setTextBoxStyle(
        juce::Slider::TextEntryBoxPosition::TextBoxLeft,
        false,
        50,
        20 );
}



AvgControl::~AvgControl()
{
    
}


// ============================================================================
void AvgControl::paint( juce::Graphics &g )
{
    m_avgSlider.setBounds( getLocalBounds() );
}



void AvgControl::resized()
{
    
}
