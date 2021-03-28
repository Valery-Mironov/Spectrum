#include "AvgControl.h"

// ****************************************************************************
// AVG CONTROL CLASS
// ****************************************************************************
AvgControl::AvgControl(
    juce::AudioProcessorValueTreeState &audioProcessorValueTreeState
) :
    mr_audioProcessorValueTreeState( audioProcessorValueTreeState )
{
    addAndMakeVisible( m_avgSlider );
    m_avgSlider.setSliderStyle( juce::Slider::SliderStyle::LinearBar );
    
    m_avgSliderAttachment =
        std::make_unique<Attachment>(
            mr_audioProcessorValueTreeState,
            "AVG_ID",
            m_avgSlider
        );
}



AvgControl::~AvgControl() {}


// ============================================================================
void AvgControl::resized()
{
    m_avgSlider.setBounds( getLocalBounds() );
}
