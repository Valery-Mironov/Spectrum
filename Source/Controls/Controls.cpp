#include <JuceHeader.h>
#include "Controls.h"

// ****************************************************************************
// CONTROLS CLASS
// ****************************************************************************
Controls::Controls( Analyser &a ) : mr_analyser( a )
{
    addAndMakeVisible( m_blockLabel );
    m_blockLabel.setText(
        "Block",
        juce::NotificationType::dontSendNotification );
    
    addAndMakeVisible( m_blockComboBox );
    m_blockComboBox.addItem( "2048", 11 );
    m_blockComboBox.addItem( "4096", 12 );
    m_blockComboBox.addItem( "8192", 13 );
    m_blockComboBox.addItem( "16384", 14 );
    m_blockComboBox.setSelectedId( 11 );
    m_blockComboBox.onChange = [ this ]
    {
        mr_analyser.setFFTBlockSize( m_blockComboBox.getSelectedId() );
    };
    
    // ------------------------------------------------------------------------
    addAndMakeVisible( m_channelLabel );
    m_channelLabel.setText(
        "Channel",
        juce::NotificationType::dontSendNotification );

    addAndMakeVisible( m_leftTextButton );
    m_leftTextButton.setButtonText( "L" );

    addAndMakeVisible( m_rightTextButton );
    m_rightTextButton.setButtonText( "R" );

    addAndMakeVisible( m_leftPlusRightTextButton );
    m_leftPlusRightTextButton.setButtonText( "L + R" );
    
    // ------------------------------------------------------------------------
    addAndMakeVisible( m_refreshLabel );
    m_refreshLabel.setText(
        "Refresh",
        juce::NotificationType::dontSendNotification );

    addAndMakeVisible( m_refreshSlider );
    m_refreshSlider.setSliderStyle(
        juce::Slider::SliderStyle::LinearBar );
    m_refreshSlider.setNumDecimalPlacesToDisplay( 0 );
    m_refreshSlider.setRange( 40, 200, 1 );
    m_refreshSlider.setValue( 60 );
    m_refreshSlider.setTextBoxStyle(
        juce::Slider::TextEntryBoxPosition::TextBoxLeft,
        false,
        50,
        20 );
    m_refreshSlider.setTextValueSuffix(" ms");
    
    // ------------------------------------------------------------------------
    addAndMakeVisible( m_avgLabel );
    m_avgLabel.setText(
        "Avg",
        juce::NotificationType::dontSendNotification );

    addAndMakeVisible( m_avgSlider );
    m_avgSlider.setSliderStyle(
        juce::Slider::SliderStyle::LinearBar );
    m_avgSlider.setRange( 1, 8, 1 );
    m_avgSlider.setValue( 1 );
    m_avgSlider.setTextBoxStyle(
        juce::Slider::TextEntryBoxPosition::TextBoxLeft,
        false,
        50,
        20 );

    // ------------------------------------------------------------------------
    addAndMakeVisible( m_graphLabel );
    m_graphLabel.setText(
        "Graph",
        juce::NotificationType::dontSendNotification );

    addAndMakeVisible( m_lineTextButon );
    m_lineTextButon.setButtonText( "Line" );

    addAndMakeVisible( m_maxTextButton );
    m_maxTextButton.setButtonText( "Max" );
    
    // ------------------------------------------------------------------------
    addAndMakeVisible( m_scaleLabel );
    m_scaleLabel.setText(
        "Scale X",
        juce::NotificationType::dontSendNotification );

    addAndMakeVisible( m_linTextButton );
    m_linTextButton.setButtonText( "Lin" );
    m_linTextButton.onClick = [ this ]
    {
//        rv_curve.setScaleType( false );
    };

    addAndMakeVisible( m_logTextButton );
    m_logTextButton.setButtonText( "Log" );
    m_logTextButton.onClick = [ this ]
    {
//        rv_curve.setScaleType( true );
    };

    addAndMakeVisible( m_stTextButton );
    m_stTextButton.setButtonText( "ST" );
    m_logTextButton.onClick = [ this ]
    {
//        rv_curve.setScaleType( true );
    };
    
    // ------------------------------------------------------------------------
    addAndMakeVisible( m_rangeTextButton );
    m_rangeTextButton.setButtonText( "Range" );

    addAndMakeVisible( m_minimumVolumeSlider );
    m_minimumVolumeSlider.setSliderStyle(
        juce::Slider::SliderStyle::LinearBar );
    m_minimumVolumeSlider.setNumDecimalPlacesToDisplay( 0 );
    m_minimumVolumeSlider.setRange( -380, 30, 1 );
    m_minimumVolumeSlider.setValue( -120 );
    m_minimumVolumeSlider.setTextBoxStyle(
        juce::Slider::TextEntryBoxPosition::TextBoxLeft,
        false,
        50,
        20 );

    addAndMakeVisible( m_maximumVolumeSlider );
    m_maximumVolumeSlider.setSliderStyle(
        juce::Slider::SliderStyle::LinearBar );
    m_maximumVolumeSlider.setNumDecimalPlacesToDisplay( 0 );
    m_maximumVolumeSlider.setRange( -200, 40, 1 );
    m_maximumVolumeSlider.setValue( 12 );
    m_maximumVolumeSlider.setTextBoxStyle(
        juce::Slider::TextEntryBoxPosition::TextBoxLeft,
        false,
        50,
        20 );
}



Controls::~Controls()
{
    
}


// ============================================================================
void Controls::paint( juce::Graphics &g )
{
    
}



void Controls::resized()
{
    auto itemHeight = 20;
    auto area = getLocalBounds().reduced( m_marginInPixels );
    
    // ------------------------------------------------------------------------
    auto sideBarArea = area.removeFromLeft( area.getWidth() / 3 );
    
    m_blockLabel.setBounds( sideBarArea.removeFromTop( itemHeight ) );
    
    sideBarArea.removeFromTop( m_marginInPixels );

    m_channelLabel.setBounds( sideBarArea.removeFromTop( itemHeight ) );
    
    sideBarArea.removeFromTop( m_marginInPixels );

    m_refreshLabel.setBounds( sideBarArea.removeFromTop( itemHeight ) );
    
    sideBarArea.removeFromTop( m_marginInPixels );

    m_avgLabel.setBounds( sideBarArea.removeFromTop( itemHeight ) );
    
    sideBarArea.removeFromTop( m_marginInPixels );

    m_graphLabel.setBounds( sideBarArea.removeFromTop( itemHeight ) );
    
    sideBarArea.removeFromTop( m_marginInPixels );

    m_scaleLabel.setBounds( sideBarArea.removeFromTop( itemHeight ) );
    
    sideBarArea.removeFromTop( m_marginInPixels );

    m_rangeTextButton.setBounds( sideBarArea.removeFromTop( itemHeight ) );
        
    // ------------------------------------------------------------------------
    m_blockComboBox.setBounds( area.removeFromTop( itemHeight ) );
    
    area.removeFromTop( m_marginInPixels );

    auto channelArea = area.removeFromTop( itemHeight );
    auto channelTextButtonWidth = channelArea.getWidth() / 3;

    m_leftTextButton.setBounds(
        channelArea.removeFromLeft( channelTextButtonWidth ) );
    m_rightTextButton.setBounds(
        channelArea.removeFromLeft( channelTextButtonWidth ) );
    m_leftPlusRightTextButton.setBounds(
        channelArea.removeFromLeft( channelTextButtonWidth ) );
    
    area.removeFromTop( m_marginInPixels );

    m_refreshSlider.setBounds( area.removeFromTop( itemHeight ) );
    
    area.removeFromTop( m_marginInPixels );

    m_avgSlider.setBounds( area.removeFromTop( itemHeight ) );
    
    area.removeFromTop( m_marginInPixels );

    auto graphArea = area.removeFromTop( itemHeight );
    auto graphTextButtonWidth = graphArea.getWidth() / 2;

    m_lineTextButon.setBounds(
        graphArea.removeFromLeft( graphTextButtonWidth ) );
    m_maxTextButton.setBounds(
        graphArea.removeFromLeft( graphTextButtonWidth ) );
    
    area.removeFromTop( m_marginInPixels );

    auto scaleArea = area.removeFromTop( itemHeight );
    auto scaleTextButtonWidth = scaleArea.getWidth() / 3;

    m_linTextButton.setBounds(
        scaleArea.removeFromLeft( scaleTextButtonWidth ) );
    m_logTextButton.setBounds(
        scaleArea.removeFromLeft( scaleTextButtonWidth ) );
    m_stTextButton.setBounds(
        scaleArea.removeFromLeft( scaleTextButtonWidth ) );
    
    area.removeFromTop( m_marginInPixels );

    auto rangeArea = area.removeFromTop( itemHeight );

    m_minimumVolumeSlider.setBounds(
        rangeArea.removeFromLeft(
            rangeArea.getWidth() / 2 ) );
    m_maximumVolumeSlider.setBounds( rangeArea );
}
