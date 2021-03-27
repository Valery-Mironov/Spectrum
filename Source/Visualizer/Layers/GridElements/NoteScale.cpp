#include "NoteScale.h"

NoteScale::NoteScale()
{
    calculateBaseTenLogarithm();
    addLabels();
}



NoteScale::~NoteScale() {}


// ============================================================================
void NoteScale::paint( juce::Graphics &g )
{
    g.setColour( m_gridColour );
    
    auto width { getWidth() };
    auto numberOfNotes { m_noteGridPoints.size() };
    auto firstNote { 0 };
    auto stepInNotes { 1 };
    
    if ( ( width / numberOfNotes ) < 5 ) {
        firstNote = 5;
        stepInNotes = 12;
    }
    
    for ( auto index { firstNote }; index < numberOfNotes; index += stepInNotes )
    {
        g.drawLine(
            m_noteGridPoints[ index ],
            0,
            m_noteGridPoints[ index ],
            getHeight()
        );
    }
    
    for ( const auto &[ note, label ] : m_labels )
    {
        label->setBounds(
            m_noteGridPoints[ note ] - 14,
            1,
            28,
            20
        );
    }
}



void NoteScale::resized()
{
    calculateFrequencyGrid();
}


// ============================================================================
void NoteScale::setGridColour( juce::Colour colour )
{
    m_gridColour = colour;
}



void NoteScale::setTextColour( juce::Colour colour )
{
    m_textColour = colour;
}


// ============================================================================
void NoteScale::calculateBaseTenLogarithm()
{
    m_baseTenLogarithm.insert(
        std::pair<int, float>(
            m_firstNote,
            std::log10f( 24.0f )
        )
    );
    
    // G0 = 24,500 Hz ( nearest note to minimum FFT frequency )
    auto pitchforkFrequency { 24.500 };
    
    for ( auto note { m_firstNote + 1 }; note < m_lastNote; ++note )
    {
        auto currentNoteFrequency
        {
            pitchforkFrequency *
            std::pow( 2.0f, static_cast<float>( note ) / 12.0f )
        };
        
        m_baseTenLogarithm.insert(
            std::pair<int, float>(
                note,
                std::log10f( currentNoteFrequency )
            )
        );
    }
    
    m_baseTenLogarithm.insert(
        std::pair<int, float>(
            m_lastNote,
            std::log10f( 24000.0f )
        )
    );
}



void NoteScale::calculateFrequencyGrid()
{
    auto sourceRangeMinimum = ( m_baseTenLogarithm.begin() )->second;
    auto sourceRangeMaximum = ( --m_baseTenLogarithm.end() )->second;
    
    auto targetRangeMinimum = 0.0f;
    auto targetRangeMaximem = static_cast<float>( getWidth() );
    
    m_noteGridPoints.clear();
    
    for ( const auto &[ note, value ] : m_baseTenLogarithm )
    {
        m_noteGridPoints[ note ] =
            juce::jmap(
                value,
                sourceRangeMinimum,
                sourceRangeMaximum,
                targetRangeMinimum,
                targetRangeMaximem
            );
    }
}



void NoteScale::addLabels()
{
    // C1 note index 5, because G0 index is 0
    for ( auto note { 5 }; note <= m_lastNote; note += 12 )
    {
        m_labels.insert(
            std::pair<int, std::unique_ptr<juce::Label>>(
                note,
                new juce::Label()
            )
        );
    }
    
    auto counter { 0 };
    
    for ( auto it { m_labels.begin() }; it != m_labels.end(); ++it )
    {
        auto &label { ( *it->second ) };
        addAndMakeVisible( label );
        label.setText(
            "C" + juce::String( counter ),
            juce::NotificationType::dontSendNotification
        );
        label.setFont( 12 );
        label.setColour( juce::Label::textColourId, m_textColour );
        label.setJustificationType( juce::Justification::centredTop );
        ++counter;
    }
}
