#include "Grid.h"

// ***************************************************************************
// GRID CLASS
// ***************************************************************************
Grid::Grid(
    const int minimumFrequencyInHertz,
    const int maximumFrequencyInHertz,
    const int minimumVolumeInDecibels,
    const int maximumVolumeInDecibels ) :
        m_maximumVolumeInDecibels( maximumVolumeInDecibels ),
        m_minimumVolumeInDecibels( minimumVolumeInDecibels )
{
    calculateBaseTenLogarithm(
        minimumFrequencyInHertz,
        maximumFrequencyInHertz );
    addLabels();
}



Grid::~Grid()
{
    
}


// ===========================================================================
void Grid::paint( juce::Graphics &g )
{
    g.setColour( m_gridColour );
    
    for ( auto y : m_volumeGridPoints )
    {
        g.drawLine(
            0,
            y,
            getWidth(),
            y );
    }
    
    for ( const auto &[ frequency, x ] : m_frequencyGridPoints )
    {
        g.drawLine(
            x,
            0,
            x,
            getHeight() );
    }
    
    for ( const auto &[ frequency, label ] : m_labels )
    {
        label->setBounds(
            m_frequencyGridPoints[ frequency ] - 14,
            1,
            28,
            20 );
    }
}



void Grid::resized()
{
    calculateFrequencyGrid();
    calculateAmplitudeGrid(
        m_minimumVolumeInDecibels,
        m_maximumVolumeInDecibels );
}


// ===========================================================================
int Grid::getOffsetInHertz( const int frequency )
{
    auto minimumForDivisions { frequency };
    auto divisionСounter { 1 };
    
    while ( m_coefficient < ( minimumForDivisions / m_coefficient ) ) {
        minimumForDivisions /= m_coefficient;
        ++divisionСounter;
    }
    
    return
        static_cast<int>(
            pow(
                static_cast<float>( m_coefficient ),
                divisionСounter ) );
}



int Grid::getCurrentFrequencyInHertz(
    const int currentFrequencyInHertz,
    const int offsetInHertz )
{
    if (
        currentFrequencyInHertz % offsetInHertz == 0 )
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

// ===========================================================================
void Grid::calculateBaseTenLogarithm(
    const int minimumFrequencyInHertz,
    const int maximumFrequencyInHertz )
{
    auto offsetInHertz
    {
        getOffsetInHertz( minimumFrequencyInHertz )
    };
    
    auto currentFrequencyInHertz
    {
        getCurrentFrequencyInHertz( minimumFrequencyInHertz, offsetInHertz )
    };
    
    if ( currentFrequencyInHertz != minimumFrequencyInHertz )
    {
        m_baseTenLogarithm[ minimumFrequencyInHertz ] =
            std::log10f(
                static_cast<float>(
                    minimumFrequencyInHertz ) );
            
    }
    
    while ( currentFrequencyInHertz < maximumFrequencyInHertz )
    {
        m_baseTenLogarithm[ currentFrequencyInHertz ] =
            std::log10f(
                static_cast<float>(
                    currentFrequencyInHertz ) );
        
        if ( offsetInHertz * m_coefficient == currentFrequencyInHertz )
        {
            offsetInHertz *= m_coefficient;
        }
        currentFrequencyInHertz += offsetInHertz;
    }
    
    if ( maximumFrequencyInHertz <= currentFrequencyInHertz)
    {
        m_baseTenLogarithm[ maximumFrequencyInHertz ] =
            std::log10f(
                static_cast<float>(
                    maximumFrequencyInHertz ) );
    }
}



void Grid::calculateFrequencyGrid()
{
    auto sourceRangeMinimum = ( m_baseTenLogarithm.begin() )->second;
    auto sourceRangeMaximum = ( --m_baseTenLogarithm.end() )->second;
    
    auto targetRangeMinimum = 0.0f;
    auto targetRangeMaximem = static_cast<float>( getWidth() );
    
    m_frequencyGridPoints.clear();
    
    for ( const auto &[ frequency, value ] : m_baseTenLogarithm )
    {
        m_frequencyGridPoints[ frequency ] =
            juce::jmap(
                value,
                sourceRangeMinimum,
                sourceRangeMaximum,
                targetRangeMinimum,
                targetRangeMaximem );
    }
}



void Grid::calculateAmplitudeGrid(
    const int miniumInDecibels,
    const int maximumInDecibels )
{
    m_volumeGridPoints.clear();
    
    auto minimum =
        miniumInDecibels < 0 ?
        miniumInDecibels * -1 :
        miniumInDecibels;
    
    auto maximum =
        maximumInDecibels < 0 ?
        maximumInDecibels * -1 :
        maximumInDecibels;
    
    auto rangeInDecibels = minimum + maximum;
    auto verticalSpace = getHeight() / ( rangeInDecibels / m_stepInDecibels );
    
    for ( auto i = 0; i < getHeight(); i += verticalSpace )
    {
        m_volumeGridPoints.push_back( i );
    }
    m_volumeGridPoints.push_back( getHeight() );
}



void Grid::addLabels()
{
    for ( auto frequency = 100; frequency <= 10000; frequency *= 10 )
    {
        m_labels.insert(
            std::pair<int, std::unique_ptr<juce::Label>>(
                frequency,
                new juce::Label() ) );
    }
    
    for ( const auto &[ frequency, label ] : m_labels ) {
        addAndMakeVisible( *label );
        label->setText(
            frequency == 100 ?
                juce::String( frequency ) :
                juce::String( frequency / 1000 ) + "k",
            juce::NotificationType::dontSendNotification );
        label->setFont( 12 );
        label->setColour( juce::Label::textColourId, m_gridColour );
        label->setJustificationType( juce::Justification::centredTop );
    }
}
