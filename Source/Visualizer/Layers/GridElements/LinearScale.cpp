#include "LinearScale.h"

LinearScale::LinearScale() { addLabels(); }
LinearScale::~LinearScale() {}


// ============================================================================
void LinearScale::paint( juce::Graphics &g )
{
    g.setColour( m_gridColour );
    
    for ( const auto &[ frequency, x ] : m_frequencyGridPoints )
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
            m_frequencyGridPoints[ frequency ] - 14,
            1,
            28,
            20
        );
    }
}



void LinearScale::resized()
{
    calculateFrequencyGrid();
}


// ============================================================================
void LinearScale::setGridColour( juce::Colour colour )
{
    m_gridColour = colour;
}



void LinearScale::setTextColour( juce::Colour colour )
{
    m_textColour = colour;
}


// ============================================================================
void LinearScale::calculateFrequencyGrid()
{
    std::vector<int> frequenciesInKilohertzSteps;
    frequenciesInKilohertzSteps.push_back( m_minimumFrequencyInHertz );
    
    for (
         auto frequency { m_kilohertz };
         frequency <= m_maximumFrequencyInHertz;
         frequency += m_kilohertz
    ) {
        frequenciesInKilohertzSteps.push_back( frequency );
    }
    
    auto targetRangeMinimum = 0.0f;
    auto targetRangeMaximem = static_cast<float>( getWidth() );
    
    m_frequencyGridPoints.clear();
    
    for ( const auto &frequency : frequenciesInKilohertzSteps )
    {
        m_frequencyGridPoints[ frequency ] =
            juce::jmap(
                static_cast<float>( frequency ),
                static_cast<float>( m_minimumFrequencyInHertz ),
                static_cast<float>( m_maximumFrequencyInHertz ),
                targetRangeMinimum,
                targetRangeMaximem
            );
    }
}



void LinearScale::addLabels()
{
    for ( auto frequency = 5000; frequency <= 20000; frequency += 5000 )
    {
        m_labels.insert(
            std::pair<int, std::unique_ptr<juce::Label>>(
                frequency,
                new juce::Label()
            )
        );
    }
    
    for ( const auto &[ frequency, label ] : m_labels )
    {
        addAndMakeVisible( *label );
        label->setText(
            juce::String( frequency / 1000 ) + "k",
            juce::NotificationType::dontSendNotification
        );
        label->setFont( 12 );
        label->setColour( juce::Label::textColourId, m_textColour );
        label->setJustificationType( juce::Justification::centredTop );
    }
}
