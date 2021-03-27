#include "PluginEditor.h"

SpectrumAudioProcessorEditor::SpectrumAudioProcessorEditor(
    SpectrumAudioProcessor &audioProcessor,
    juce::AudioProcessorValueTreeState &audioProcessorValueTreeState,
    Analyser &analyser
) : AudioProcessorEditor( &audioProcessor ),
    mr_audioProcessor( audioProcessor ),
    m_visualizer( audioProcessorValueTreeState, analyser ),
    m_controls( audioProcessorValueTreeState )
{
    addAndMakeVisible( m_visualizer );
    
    addAndMakeVisible( m_controls );
    m_controls.setMarginInPixels( m_marginInPixels );
    
    setResizable( true, true );
    setSize( 600, 240 );
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
    if ( getHeight() < 240 ) { setSize( getWidth(), 240 ); }
    
    auto area = getLocalBounds().reduced( m_marginInPixels );
    
    m_controls.setBounds( area.removeFromLeft( area.getWidth() / 3 ) );
    m_visualizer.setBounds( area );
}
