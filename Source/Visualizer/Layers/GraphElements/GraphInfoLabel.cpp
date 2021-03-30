#include "GraphInfoLabel.h"

GraphInfoLabel::GraphInfoLabel(
    juce::AudioProcessorValueTreeState &audioProcessorValueTreeState
) :
    mr_audioProcessorValueTreeState( audioProcessorValueTreeState )
{
    
    addAndMakeVisible( m_frequencyLabel );
    m_frequencyLabel.setColour( juce::Label::ColourIds::textColourId, m_colour );
    m_frequencyLabel.setJustificationType( juce::Justification::bottomRight );
    m_frequencyLabel.setText( "113 Hz", juce::dontSendNotification );
    
    
    addAndMakeVisible( m_noteLabel );
    m_noteLabel.setColour( juce::Label::ColourIds::textColourId, m_colour );
    m_noteLabel.setJustificationType( juce::Justification::centredRight );
    m_noteLabel.setText( "A1", juce::dontSendNotification );
    
    addAndMakeVisible( m_volumeLabel );
    m_volumeLabel.setColour( juce::Label::ColourIds::textColourId, m_colour );
    m_volumeLabel.setJustificationType( juce::Justification::topRight );
    m_volumeLabel.setText( "-47.0 dB", juce::dontSendNotification );
}



GraphInfoLabel::~GraphInfoLabel() {}


// ============================================================================
void GraphInfoLabel::paint( juce::Graphics &g )
{
    juce::Path path;
    path.addRoundedRectangle( m_rectangle, m_marginInPixels );
    
    g.setColour( m_backgroundColour );
    g.fillPath( path );
    g.setColour( m_colour );
    g.strokePath( path, juce::PathStrokeType( 1.0f ) );
}



void GraphInfoLabel::resized()
{
    m_rectangle.setBounds(
        m_marginInPixels,
        getHeight() - m_marginInPixels - m_height,
        m_width,
        m_height
    );
    
    auto area { m_rectangle };
    auto itemHeight { 20 };
    
    m_frequencyLabel.setBounds( area.removeFromTop( itemHeight ) );
    m_noteLabel.setBounds( area.removeFromTop( itemHeight ) );
    m_volumeLabel.setBounds( area.removeFromTop( itemHeight ) );
}


// ============================================================================
void GraphInfoLabel::setBackgroundColour( const juce::Colour &colour )
{
    m_backgroundColour = colour;
}



void GraphInfoLabel::setColour( const juce::Colour &colour )
{
    m_colour = colour;
}


// ============================================================================
void GraphInfoLabel::setMarginInPixels( const int margin )
{
    m_marginInPixels = margin;
}


// ============================================================================
void GraphInfoLabel::setData( const float x, const float y, const bool isLogarithmic )
{
    auto frequency { getFrequency( x, isLogarithmic ) };
    auto note { getNote( frequency ) };
    auto volume { getVolume( y ) };
    
    m_frequencyLabel.setText( juce::String( frequency ) + " Hz", juce::dontSendNotification );
    m_noteLabel.setText( note , juce::dontSendNotification );
    m_volumeLabel.setText( juce::String( volume ) + " dB", juce::dontSendNotification );
}


// ============================================================================
int GraphInfoLabel::getFrequency( const float x, const bool isLogarithmic )
{
    int frequency { 0 };
    
    if ( isLogarithmic )
    {
        auto logarithm
        {
            juce::jmap(
                x,
                0.0f,
                static_cast<float>( getWidth() ),
                std::log10f( 24.0f ),
                std::log10f( 24000.0f )
            )
        };
        
        frequency = static_cast<int>( std::pow( 10, logarithm ) );
    }
    else
    {
        frequency =
            juce::jmap(
                static_cast<int>( x ),
                0,
                getWidth(),
                24,
                24000
            );
    }
    
    return frequency;
}



juce::String GraphInfoLabel::getNote( const int frequency )
{
    std::array<juce::String, 12> notes
    {
        "C", "C#", "D", "D#", "E", "F", "F#", "G", "G#", "A", "A#", "B"
    };
    
    // G0 = 24,500 Hz ( nearest note to minimum FFT frequency )
    
    auto note { 0 };
    auto pitchforkFrequency { 24.500 };
    auto previousNoteFrequency { pitchforkFrequency * std::pow( 2.0f, static_cast<int>( note - 1 ) / 12.0f ) };
    auto currentNoteFrequency { pitchforkFrequency };
    auto octave { -1 };
    
    while ( currentNoteFrequency - ( ( currentNoteFrequency - previousNoteFrequency ) / 2.0f ) < frequency )
    {
        previousNoteFrequency = pitchforkFrequency * std::pow( 2.0f, static_cast<int>( note - 1 ) / 12.0f );
        currentNoteFrequency = pitchforkFrequency * std::pow( 2.0f, static_cast<int>( note ) / 12.0f );
        ++note;
        if ( ( note + 5 ) % 12 == 0 ) ++octave;
    }
    
    return notes.at( ( note + 5 ) % 12 ) + juce::String( octave );
}



float GraphInfoLabel::getVolume( const float y )
{
    auto volume
    {
        juce::jmap(
            y,
            0.0f,
            static_cast<float>( getHeight() ),
            mr_audioProcessorValueTreeState.getRawParameterValue( "MAXIMUM_ID" )->load(),
            mr_audioProcessorValueTreeState.getRawParameterValue( "MINIMUM_ID" )->load()
        )
    };
    
    return volume;
}
