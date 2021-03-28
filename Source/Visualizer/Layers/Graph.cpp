#include "Graph.h"

Graph::Graph(
    juce::AudioProcessorValueTreeState &audioProcessorValueTreeState,
    Analyser &analyser
) :
    mr_audioProcessorValueTreeState( audioProcessorValueTreeState ),
    mr_analyser( analyser ),
    m_graphMaximumsLine( analyser ),
    m_graphLine( analyser ),
    m_graphBins( analyser )
{
    addChildComponent( m_graphMaximumsLine );
    m_graphMaximumsLine.setColour( m_volumeMaximumsGraphColour );
    
    addChildComponent( m_graphLine );
    m_graphLine.setColour( m_volumeGraphColour );
    
    addChildComponent( m_graphBins );
    m_graphBins.setColour( m_volumeGraphColour );
    
    mr_audioProcessorValueTreeState.addParameterListener( "REFRESH_ID", this );
    mr_audioProcessorValueTreeState.addParameterListener( "BINS_ID", this );
    mr_audioProcessorValueTreeState.addParameterListener( "MAX_ID", this );
    mr_audioProcessorValueTreeState.addParameterListener( "LIN_ID", this );
    mr_audioProcessorValueTreeState.addParameterListener( "LOG_ID", this );
    mr_audioProcessorValueTreeState.addParameterListener( "ST_ID", this );
    
    addMouseListener( this, true );
    startTimer( 60 );
}



Graph::~Graph()
{
    stopTimer();
}


// ============================================================================
void Graph::paint( juce::Graphics &g )
{
    g.setColour( juce::Colours::white );
    g.drawText(
        juce::String( mr_analyser.getCurrentMaximumInDecibels() ),
        getLocalBounds(),
        juce::Justification::centred
    );
}



void Graph::resized()
{
    m_graphMaximumsLine.setBounds( getLocalBounds() );
    m_graphLine.setBounds( getLocalBounds() );
    m_graphBins.setBounds( getLocalBounds() );
}


// ============================================================================
void Graph::mouseDown( const juce::MouseEvent &event )
{
    mr_analyser.resetScopeMaximumsData();
}


// ============================================================================
void Graph::timerCallback()
{
    if ( mr_analyser.getNextFFTBlockStatus() )
    {
        mr_analyser.calculateNextFrameOfSpectrum();
        mr_analyser.setNextFFTBlockStatus( false );
        
        m_graphMaximumsLine.setScaleType( m_scaleTypeIsLogarithmic.load() );
        m_graphLine.setScaleType( m_scaleTypeIsLogarithmic.load() );
        m_graphBins.setScaleType( m_scaleTypeIsLogarithmic.load() );
        
        m_graphMaximumsLine.setVisible( m_maximumVolumesIsVisible.load() );
        m_graphLine.setVisible( m_graphStyleIsLine.load() );
        m_graphBins.setVisible( ! m_graphStyleIsLine.load() );
        
        repaint();
    }
}


// ============================================================================
void Graph::setGraphColour( juce::Colour colour )
{
    m_volumeGraphColour = colour;
}



void Graph::setGraphMaximumsColour( juce::Colour colour )
{
    m_volumeMaximumsGraphColour = colour;
}


// ============================================================================
void Graph::setTimerInterval( const int milliseconds )
{
    stopTimer();
    startTimer( milliseconds );
}



void Graph::setGraphStyleAsLine( const bool isLine )
{
    m_graphStyleIsLine.store( isLine );
}



void Graph::setMaximumVolumesVisible( const bool isVisible )
{
    m_maximumVolumesIsVisible.store( isVisible );
}



void Graph::setScaleTypeAsLogarithmic( const bool isLogarithmic )
{
    m_scaleTypeIsLogarithmic.store( isLogarithmic );
}


// ============================================================================
void Graph::parameterChanged(
    const juce::String &parameterID,
    float newValue
) {
    if ( parameterID == "REFRESH_ID" )
    {
        setTimerInterval( static_cast<int>( newValue ) );
    }
    if ( parameterID == "BINS_ID" )
    {
        setGraphStyleAsLine( static_cast<bool>( newValue ) );
    }
    else if ( parameterID == "MAX_ID" )
    {
        setMaximumVolumesVisible( static_cast<bool>( newValue ) );
    }
    else if ( parameterID == "LIN_ID" )
    {
        setScaleTypeAsLogarithmic( false );
    }
    else if ( parameterID == "LOG_ID" || parameterID == "ST_ID" )
    {
        setScaleTypeAsLogarithmic( true );
    }
}
