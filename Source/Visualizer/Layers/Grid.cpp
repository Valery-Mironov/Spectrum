#include "Grid.h"

Grid::Grid(
    juce::AudioProcessorValueTreeState &audioProcessorValueTreeState
) : mr_audioProcessorValueTreeState( audioProcessorValueTreeState )
{
    addChildComponent( m_logarithmicScale );
    addChildComponent( m_linearScale );
    addChildComponent( m_noteScale );
        
    mr_audioProcessorValueTreeState.addParameterListener( "LIN_ID", this );
    mr_audioProcessorValueTreeState.addParameterListener( "LOG_ID", this );
    mr_audioProcessorValueTreeState.addParameterListener( "ST_ID", this );
    mr_audioProcessorValueTreeState.addParameterListener( "MAXIMUM_ID", this );
    mr_audioProcessorValueTreeState.addParameterListener( "MINIMUM_ID", this );
}



Grid::~Grid() {}


// ===========================================================================
void Grid::paint( juce::Graphics &g )
{
    g.setColour( m_gridColour );
    g.drawRect( getLocalBounds() );
    
    calculateAmplitudeGrid();
    addLabels();
        
    for ( const auto y : m_volumeGridPoints )
    {
        g.drawLine(
            0.0f,
            y,
            static_cast<float>( getWidth() ),
            y
        );
    }
    
    for ( const auto &[ volume, label ] : m_labels )
    {
        label->setBounds(
            0.0f,
            juce::jmap(
                static_cast<float>( volume ),
                static_cast<float>( m_maximumVolumeInDecibels.load() ),
                static_cast<float>( m_minimumVolumeInDecibels.load() ),
                0.0f,
                static_cast<float>( getHeight() )
            ) - 7.0f,
            28.0f,
            20.0f
        );
    }
    
    m_linearScale.setVisible( m_gridStyleIsLinear );
    m_logarithmicScale.setVisible( m_gridStyleIsLogarithmic );
    m_noteScale.setVisible( m_gridStyleIsST );
}



void Grid::resized()
{
    m_linearScale.setBounds( getLocalBounds() );
    m_logarithmicScale.setBounds( getLocalBounds() );
    m_noteScale.setBounds( getLocalBounds() );
    
    repaint();
}


// ============================================================================
void Grid::setGridColour( juce::Colour colour )
{
    m_gridColour = colour;
}



void Grid::setTextColour( juce::Colour colour )
{
    m_textColour = colour;
}


// ============================================================================
void Grid::parameterChanged(
    const juce::String &parameterID,
    float newValue
) {
    if ( parameterID == "LIN_ID" )
    {
        setGridStyle( GridStyles::linear );
    }
    else if ( parameterID == "LOG_ID" )
    {
        setGridStyle( GridStyles::logarithmic );
    }
    else if ( parameterID == "ST_ID" )
    {
        setGridStyle( GridStyles::st );
    }
    else if ( parameterID == "MAXIMUM_ID" || parameterID == "MINIMUM_ID" )
    {
        setVolumeRangeInDecibels(
            static_cast<int>(
                mr_audioProcessorValueTreeState.getRawParameterValue(
                    "MAXIMUM_ID"
                )->load()
            ),
            static_cast<int>(
                mr_audioProcessorValueTreeState.getRawParameterValue(
                    "MINIMUM_ID"
                )->load()
            )
        );
    }
}


// ============================================================================
void Grid::setGridStyle( GridStyles style )
{
    switch ( style  ) {
        case GridStyles::linear:
            m_gridStyleIsLinear = true;
            m_gridStyleIsLogarithmic = false;
            m_gridStyleIsST = false;
            break;
        case GridStyles::logarithmic:
            m_gridStyleIsLinear = false;
            m_gridStyleIsLogarithmic = true;
            m_gridStyleIsST = false;
            break;
        case GridStyles::st:
            m_gridStyleIsLinear = false;
            m_gridStyleIsLogarithmic = false;
            m_gridStyleIsST = true;
            break;
        default:
            DBG( "Error! Unknown grid style." );
            break;
    }
    
    repaint();
}



void Grid::setVolumeRangeInDecibels( int maximum, int minimum )
{
    if ( maximum - 10 < minimum ) { minimum = maximum - 10; }
    
    m_maximumVolumeInDecibels.store( maximum );
    m_minimumVolumeInDecibels.store( minimum );
}


// ============================================================================
void Grid::calculateAmplitudeGrid()
{
    const auto maximum { m_maximumVolumeInDecibels.load() };
    const auto minimum { m_minimumVolumeInDecibels.load() };
    
    int rangeInDecibels;
    
    if ( maximum < 0 )
    {
        rangeInDecibels = ( minimum - maximum ) * -1;
    }
    else if ( 0 <= minimum )
    {
        rangeInDecibels = maximum - minimum;
    }
    else
    {
        rangeInDecibels = maximum + minimum * -1;
    }
    
    m_offsetInDecibels.store( 0 );
    auto offset { 0.0f };
    
    while ( offset < 16.0f )
    {
        m_offsetInDecibels.store( m_offsetInDecibels.load() + 6 );
        
        offset =
            juce::jmap(
                static_cast<float>( m_offsetInDecibels.load() ),
                0.0f,
                static_cast<float>( rangeInDecibels ),
                0.0f,
                static_cast<float>( getHeight() )
            );
    }
    
    m_firstOffsetInDecibels.store( maximum );
    
    while (
        m_firstOffsetInDecibels.load() %
        m_offsetInDecibels.load() !=
        0
    ) {
        m_firstOffsetInDecibels.store( m_firstOffsetInDecibels.load() - 1 );
    }
    
    const auto first
    {
        juce::jmap(
            static_cast<float>( m_firstOffsetInDecibels.load() ),
            static_cast<float>( maximum ),
            static_cast<float>( minimum ),
            0.0f,
            static_cast<float>( getHeight() )
        )
    };
    
    const auto height { static_cast<float>( getHeight() ) };
    m_volumeGridPoints.clear();
        
    for ( auto position { first }; position < height; position += offset )
    {
        m_volumeGridPoints.push_back( position );
    }
}



void Grid::addLabels()
{
    auto volume { m_firstOffsetInDecibels.load() };
    const auto offset { m_offsetInDecibels.load() };
    const auto minimum { m_minimumVolumeInDecibels.load() };
    
    m_labels.clear();
    
    while ( minimum < volume - offset )
    {
        volume -= offset;
        m_labels.insert(
            std::pair<int, std::unique_ptr<juce::Label>>(
                volume,
                new juce::Label()
            )
        );
    }
    
    for ( const auto &[ volume, label ] : m_labels ) {
        addAndMakeVisible( *label );
        label->setText(
            juce::String( volume ),
            juce::NotificationType::dontSendNotification
        );
        label->setFont( 12 );
        label->setColour( juce::Label::textColourId, m_textColour );
        label->setJustificationType( juce::Justification::centredTop );
    }
}
