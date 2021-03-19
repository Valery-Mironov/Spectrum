#include "ScaleYControls.h"

ScaleYControls::ScaleYControls( Analyser &a ) :
    mr_analyser( a )
{
    addAndMakeVisible( m_rangeTextButton );
    m_rangeTextButton.setButtonText( "Range" );
    m_rangeTextButton.setClickingTogglesState( true );
    m_rangeTextButton.setToggleState( true, juce::dontSendNotification );
    m_rangeTextButton.onClick = [ this ]
    {
        if ( m_rangeTextButton.getToggleState() == true )
        {
            m_rangeTextButton.setButtonText( "Range" );
            m_maximumVolumeSlider.setEnabled( true );
            m_minimumVolumeSlider.setEnabled( true );
            mr_analyser.setVolumeScaleDynamicRange( false );
        }
        else
        {
            m_rangeTextButton.setButtonText( "Auto" );
            m_maximumVolumeSlider.setEnabled( false );
            m_minimumVolumeSlider.setEnabled( false );
            mr_analyser.setVolumeScaleDynamicRange( true );
        }
    };
    
    addAndMakeVisible( m_maximumVolumeSlider );
    m_maximumVolumeSlider.setSliderStyle(
        juce::Slider::SliderStyle::LinearBar );
    m_maximumVolumeSlider.setNumDecimalPlacesToDisplay( 0 );
    m_maximumVolumeSlider.setRange( -200, 40, 1 );
    m_maximumVolumeSlider.setValue( 12, juce::dontSendNotification );
    m_maximumVolumeSlider.setTextBoxStyle(
        juce::Slider::TextEntryBoxPosition::TextBoxLeft,
        false,
        50,
        20 );
    m_maximumVolumeSlider.onValueChange = [ this ]
    {
        auto maximumVolume { m_maximumVolumeSlider.getValue() };
        m_minimumVolumeSlider.setRange(
            maximumVolume - 180,
            maximumVolume - 10,
            1 );
        
        auto minimumVolume { m_minimumVolumeSlider.getValue() };
        
        mr_analyser.setVolumeRangeInDecibels(
            static_cast<float>( minimumVolume ),
            static_cast<float>( maximumVolume ) );
    };
    
    addAndMakeVisible( m_minimumVolumeSlider );
    m_minimumVolumeSlider.setSliderStyle(
        juce::Slider::SliderStyle::LinearBar );
    m_minimumVolumeSlider.setNumDecimalPlacesToDisplay( 0 );
    m_minimumVolumeSlider.setRange( -380, 30, 1 );
    m_minimumVolumeSlider.setValue( -120, juce::dontSendNotification );
    m_minimumVolumeSlider.setTextBoxStyle(
        juce::Slider::TextEntryBoxPosition::TextBoxLeft,
        false,
        50,
        20 );
    m_minimumVolumeSlider.onValueChange = [ this ]
    {
        auto minimumVolume { m_minimumVolumeSlider.getValue() };
        auto maximumVolume { m_maximumVolumeSlider.getValue() };
        mr_analyser.setVolumeRangeInDecibels(
            static_cast<float>( minimumVolume ),
            static_cast<float>( maximumVolume ) );
    };
}



ScaleYControls::~ScaleYControls()
{
    
}


// ============================================================================
void ScaleYControls::paint( juce::Graphics &g )
{
    
}



void ScaleYControls::resized()
{
    auto indent { 3 };
    auto area { getLocalBounds() };
    auto buttonWidth
    {
        ( area.getWidth() - indent * 2 ) / 3
    };
    
    m_rangeTextButton.setBounds( area.removeFromLeft( buttonWidth ) );
    area.removeFromLeft( indent );
    
    m_minimumVolumeSlider.setBounds( area.removeFromRight( buttonWidth ) );
    area.removeFromRight( indent );
    
    m_maximumVolumeSlider.setBounds( area );
}
