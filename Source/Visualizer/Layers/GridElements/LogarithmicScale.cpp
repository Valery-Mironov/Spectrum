#include "LogarithmicScale.h"

LogarithmicScale::LogarithmicScale()
{
    calculateBaseTenLogarithm();
    addLabels();
}



LogarithmicScale::~LogarithmicScale() {}


// ============================================================================
void LogarithmicScale::paint( juce::Graphics &g )
{
    g.setColour( m_gridColour );
    
    for ( const auto &[ frequency, x ] : m_noteGridPoints )
    {
        g.drawLine(
            x,
            0,
            x,
            getHeight()
        );
    }
    
    for ( const auto &[ frequency, label ] : m_labels )
    {
        label->setBounds(
            m_noteGridPoints[ frequency ] - 14,
            1,
            28,
            20
        );
    }
}



void LogarithmicScale::resized()
{
    calculateFrequencyGrid();
}


// ============================================================================
void LogarithmicScale::setGridColour( juce::Colour colour )
{
    m_gridColour = colour;
}



void LogarithmicScale::setTextColour( juce::Colour colour )
{
    m_textColour = colour;
}


// ===========================================================================
void LogarithmicScale::calculateBaseTenLogarithm()
{
    auto offsetInHertz
    {
        getOffsetInHertz( m_minimumFrequencyInHertz )
    };
    
    auto currentFrequencyInHertz
    {
        getCurrentFrequencyInHertz( m_minimumFrequencyInHertz, offsetInHertz )
    };
    
    if ( currentFrequencyInHertz != m_minimumFrequencyInHertz )
    {
        m_baseTenLogarithm[ m_minimumFrequencyInHertz ] =
            std::log10f(
                static_cast<float>( m_minimumFrequencyInHertz )
            );
            
    }
    
    while ( currentFrequencyInHertz < m_maximumFrequencyInHertz )
    {
        m_baseTenLogarithm[ currentFrequencyInHertz ] =
            std::log10f(
                static_cast<float>( currentFrequencyInHertz )
            );
        
        if ( offsetInHertz * m_coefficient == currentFrequencyInHertz )
        {
            offsetInHertz *= m_coefficient;
        }
        currentFrequencyInHertz += offsetInHertz;
    }
    
    if ( m_maximumFrequencyInHertz <= currentFrequencyInHertz)
    {
        m_baseTenLogarithm[ m_maximumFrequencyInHertz ] =
            std::log10f(
                static_cast<float>( m_maximumFrequencyInHertz )
            );
    }
}



void LogarithmicScale::calculateFrequencyGrid()
{
    auto sourceRangeMinimum = ( m_baseTenLogarithm.begin() )->second;
    auto sourceRangeMaximum = ( --m_baseTenLogarithm.end() )->second;
    
    auto targetRangeMinimum = 0.0f;
    auto targetRangeMaximem = static_cast<float>( getWidth() );
    
    m_noteGridPoints.clear();
    
    for ( const auto &[ frequency, value ] : m_baseTenLogarithm )
    {
        m_noteGridPoints[ frequency ] =
            juce::jmap(
                value,
                sourceRangeMinimum,
                sourceRangeMaximum,
                targetRangeMinimum,
                targetRangeMaximem
            );
    }
}



void LogarithmicScale::addLabels()
{
    for ( auto frequency = 100; frequency <= 10000; frequency *= 10 )
    {
        m_labels.insert(
            std::pair<int, std::unique_ptr<juce::Label>>(
                frequency,
                new juce::Label()
            )
        );
    }
    
    for ( const auto &[ frequency, label ] : m_labels ) {
        addAndMakeVisible( *label );
        label->setText(
            frequency == 100 ?
            juce::String( frequency ) :
            juce::String( frequency / 1000 ) + "k",
            juce::NotificationType::dontSendNotification
        );
        label->setFont( 12 );
        label->setColour( juce::Label::textColourId, m_textColour );
        label->setJustificationType( juce::Justification::centredTop );
    }
}


// ===========================================================================
int LogarithmicScale::getOffsetInHertz( const int frequency )
{
    auto minimumForDivisions { frequency };
    auto divisionСounter { 1 };
    
    while ( m_coefficient < ( minimumForDivisions / m_coefficient ) )
    {
        minimumForDivisions /= m_coefficient;
        ++divisionСounter;
    }
    
    return
        static_cast<int>(
            pow( static_cast<float>( m_coefficient ), divisionСounter )
        );
}



int LogarithmicScale::getCurrentFrequencyInHertz(
    const int currentFrequencyInHertz,
    const int offsetInHertz
) {
    if ( currentFrequencyInHertz % offsetInHertz == 0 )
    {
        return currentFrequencyInHertz;
    }
    else
    {
        auto newFrequency { currentFrequencyInHertz };
        newFrequency -= currentFrequencyInHertz % offsetInHertz;
        return newFrequency + offsetInHertz;
    }
}
