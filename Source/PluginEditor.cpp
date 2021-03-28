#include "PluginEditor.h"

SpectrumAudioProcessorEditor::SpectrumAudioProcessorEditor(
    SpectrumAudioProcessor &audioProcessor,
    juce::AudioProcessorValueTreeState &audioProcessorValueTreeState,
    Analyser &analyser
) :
    AudioProcessorEditor( &audioProcessor ),
    mr_audioProcessor( audioProcessor ),
    m_visualizer( audioProcessorValueTreeState, analyser ),
    m_controls( audioProcessorValueTreeState )
{
    addAndMakeVisible( m_controls );
    m_controls.setMarginInPixels( m_marginInPixels );
    
    addAndMakeVisible( m_visualizer );
    m_visualizer.setMarginInPixels( m_marginInPixels );
    m_visualizer.setBackgroundColour( juce::Colour( 0xff323232 ) );
    
    setResizable( true, true );
    setSize( 680, 255 );
}



SpectrumAudioProcessorEditor::~SpectrumAudioProcessorEditor() {}


// ============================================================================
void SpectrumAudioProcessorEditor::paint( juce::Graphics &g )
{
    g.fillAll( backgroundColour );
}



void SpectrumAudioProcessorEditor::resized()
{
    if ( getWidth() < 600 ) { setSize( 600, getHeight() ); }
    if ( getHeight() < 255 ) { setSize( getWidth(), 255 ); }
    
    auto area = getLocalBounds().reduced( m_marginInPixels );
    
    m_controls.setBounds( area.removeFromLeft( 200 ) );
    m_visualizer.setBounds( area );
}
