#include "ScaleYControls.h"

ScaleYControls::ScaleYControls(
    juce::AudioProcessorValueTreeState &audioProcessorValueTreeState
) : mr_audioProcessorValueTreeState( audioProcessorValueTreeState )
{
    addAndMakeVisible( m_rangeModeTextButton );
    m_rangeModeTextButton.setButtonText( "Range" );
    m_rangeModeTextButton.setClickingTogglesState( true );
    m_rangeModeTextButton.onClick = [ this ]
    {
        if ( m_rangeModeTextButton.getToggleState() == true )
        {
            m_rangeModeTextButton.setButtonText( "Range" );
            m_maximumVolumeSlider.setEnabled( true );
            m_minimumVolumeSlider.setEnabled( true );
        }
        else
        {
            m_rangeModeTextButton.setButtonText( "Auto" );
            m_maximumVolumeSlider.setEnabled( false );
            m_minimumVolumeSlider.setEnabled( false );
        }
    };
    
    m_rangeTextButtonAttachment =
        std::make_unique<ButtonAttachment>(
            mr_audioProcessorValueTreeState,
            "RANGE_ID",
            m_rangeModeTextButton
        );
    
    addAndMakeVisible( m_maximumVolumeSlider );
    m_maximumVolumeSlider.setSliderStyle( juce::Slider::LinearBar );
    m_maximumVolumeSlider.onValueChange = [ this ]
    {
        auto maximumVolume { m_maximumVolumeSlider.getValue() };
        m_minimumVolumeSlider.setRange(
            maximumVolume - 180,
            maximumVolume - 10,
            1
        );
    };
    
    m_maximumVolumeSliderAttachment =
        std::make_unique<SliderAttachment>(
            mr_audioProcessorValueTreeState,
            "MAXIMUM_ID",
            m_maximumVolumeSlider
        );
    
    addAndMakeVisible( m_minimumVolumeSlider );
    m_minimumVolumeSlider.setSliderStyle( juce::Slider::LinearBar );
    
    m_minimumVolumeSliderAttachment =
        std::make_unique<SliderAttachment>(
            mr_audioProcessorValueTreeState,
            "MINIMUM_ID",
            m_minimumVolumeSlider
        );
}


ScaleYControls::~ScaleYControls() {}


// ============================================================================
void ScaleYControls::resized()
{
    auto indent { 3 };
    auto area { getLocalBounds() };
    auto buttonWidth
    {
        ( area.getWidth() - indent * 2 ) / 3
    };
    
    m_rangeModeTextButton.setBounds( area.removeFromLeft( buttonWidth ) );
    area.removeFromLeft( indent );
    
    m_minimumVolumeSlider.setBounds( area.removeFromRight( buttonWidth ) );
    area.removeFromRight( indent );
    
    m_maximumVolumeSlider.setBounds( area );
}
