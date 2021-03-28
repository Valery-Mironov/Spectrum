#include "Controls.h"

Controls::Controls(
    juce::AudioProcessorValueTreeState &audioProcessorValueTreeState
) :
    m_blockControl( audioProcessorValueTreeState ),
    m_channelControls( audioProcessorValueTreeState ),
    m_refreshControl( audioProcessorValueTreeState ),
    m_avgControl( audioProcessorValueTreeState ),
    m_graphControls( audioProcessorValueTreeState ),
    m_scaleXControls( audioProcessorValueTreeState ),
    m_scaleYControls( audioProcessorValueTreeState )
{
    getLookAndFeel().setColour( juce::Label::textColourId, juce::Colour( 0xff141414 ) );
    
    addAndMakeVisible( m_blockLabel );
    m_blockLabel.setText( "Block", juce::dontSendNotification );
    addAndMakeVisible( m_blockControl );
    
    addAndMakeVisible( m_firstSeparator );
    
    addAndMakeVisible( m_channelLabel );
    m_channelLabel.setText( "Channel", juce::dontSendNotification );
    addAndMakeVisible( m_channelControls );
    
    addAndMakeVisible( m_secondSeparator );
    
    addAndMakeVisible( m_refreshLabel );
    m_refreshLabel.setText( "Refresh", juce::dontSendNotification );
    addAndMakeVisible( m_refreshControl );
    
    addAndMakeVisible( m_avgLabel );
    m_avgLabel.setText( "Avg", juce::dontSendNotification );
    addAndMakeVisible( m_avgControl );
    
    addAndMakeVisible( m_thirdSeparator );
        
    addAndMakeVisible( m_graphLabel );
    m_graphLabel.setText( "Graph", juce::dontSendNotification );
    addAndMakeVisible( m_graphControls );
    
    addAndMakeVisible( m_scaleLabel );
    m_scaleLabel.setText( "Scale X", juce::dontSendNotification );
    addAndMakeVisible( m_scaleXControls );
    
    addAndMakeVisible( m_scaleYControls );
}


// ============================================================================
void Controls::resized()
{
    auto area { getLocalBounds() };
    auto itemHeight { 20 };
    auto line { area.removeFromTop( itemHeight ) };
    auto column { area.getWidth() / 3 };
    
    m_blockLabel.setBounds( line.removeFromLeft( column ) );
    m_blockControl.setBounds( line );
    
    m_firstSeparator.setBounds( area.removeFromTop( itemHeight ) );
    
    line = area.removeFromTop( itemHeight );
    m_channelLabel.setBounds( line.removeFromLeft( column ) );
    m_channelControls.setBounds( line );
    
    m_secondSeparator.setBounds( area.removeFromTop( itemHeight ) );
    
    line = area.removeFromTop( itemHeight );
    m_refreshLabel.setBounds( line.removeFromLeft( column ) );
    m_refreshControl.setBounds( line );
    
    auto offset { m_marginInPixels / 2 };
    
    area.removeFromTop( offset );
    
    line = area.removeFromTop( itemHeight );
    m_avgLabel.setBounds( line.removeFromLeft( column ) );
    m_avgControl.setBounds( line );
    
    m_thirdSeparator.setBounds( area.removeFromTop( itemHeight ) );
    
    line = area.removeFromTop( itemHeight );
    m_graphLabel.setBounds( line.removeFromLeft( column ) );
    m_graphControls.setBounds( line );
    
    area.removeFromTop( offset );
    
    line = area.removeFromTop( itemHeight );
    m_scaleLabel.setBounds( line.removeFromLeft( column ) );
    m_scaleXControls.setBounds( line );
    
    area.removeFromTop( offset );
    
    line = area.removeFromTop( itemHeight );
    m_scaleYControls.setBounds( line );
}


// ========================================================================
void Controls::setMarginInPixels( const int margin )
{
    m_marginInPixels = margin;
}
