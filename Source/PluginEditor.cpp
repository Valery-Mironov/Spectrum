#include "PluginProcessor.h"
#include "PluginEditor.h"

// ****************************************************************************
// SPECTRUM AUDIO PROCESSOR EDITOR CLASS
// ****************************************************************************
SpectrumAudioProcessorEditor::SpectrumAudioProcessorEditor(
    SpectrumAudioProcessor &p,
    Analyser &a ) :
        AudioProcessorEditor( &p ),
        mr_audioProcessor( p ),
        m_controls( a ),
        m_visualizer( a )
{
    addAndMakeVisible( m_controls );
    addAndMakeVisible( m_visualizer );
    
    setResizable( true, true );
    setSize( 600, 240 );
}



SpectrumAudioProcessorEditor::~SpectrumAudioProcessorEditor()
{
    
}


// ============================================================================
void SpectrumAudioProcessorEditor::paint( juce::Graphics &g )
{
    g.fillAll( backgroundColour );
}



void SpectrumAudioProcessorEditor::resized()
{
    // Найти более изящное решение для указания минимальных размеров окна
    if ( getWidth() < 600 || getHeight() < 240 )
    {
        setSize( 600, 240 );
    }
    
    auto area = getLocalBounds().reduced( m_marginInPixels );
    
    m_controls.setBounds( area.removeFromLeft( area.getWidth() / 3 ) );
    m_visualizer.setBounds( area );
}
