#include "RefreshControl.h"

RefreshControl::RefreshControl( Graph &c ) : mr_curve( c )
{
    addAndMakeVisible( m_refreshSlider );
    m_refreshSlider.setSliderStyle(
        juce::Slider::SliderStyle::LinearBar );
    m_refreshSlider.setNumDecimalPlacesToDisplay( 0 );
    m_refreshSlider.setRange( 40, 200, 1 );
    m_refreshSlider.setValue(
        60,
        juce::dontSendNotification );
    m_refreshSlider.setTextBoxStyle(
        juce::Slider::TextEntryBoxPosition::TextBoxLeft,
        false,
        50,
        20 );
    m_refreshSlider.setTextValueSuffix(" ms");
    m_refreshSlider.onValueChange = [ this ]
    {
        mr_curve.setTimerInterval(
            static_cast<int>(
                m_refreshSlider.getValue() ) );
    };
}



RefreshControl::~RefreshControl()
{
    
}


// ============================================================================
void RefreshControl::paint( juce::Graphics &g )
{
    
}



void RefreshControl::resized()
{
    m_refreshSlider.setBounds( getLocalBounds() );
}
