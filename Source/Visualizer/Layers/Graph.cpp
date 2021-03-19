#include "Graph.h"

Graph::Graph( Analyser &analyser ) :
    mr_analyser( analyser ),
    m_graphMaximumsLine( analyser ),
    m_graphLine( analyser ),
    m_graphBins( analyser )
{
    addChildComponent( m_graphMaximumsLine );
    addChildComponent( m_graphLine );
    addChildComponent( m_graphBins );
    setGraphStyleAsBins( false );
    maximumVolumesAreShown( true );
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
    
    std::cout << std::endl;
    std::cout << "----------------> GRAPH <----------------";
    std::cout << std::endl;
    std::cout << "Scope maximums data reset.";
    std::cout << std::endl;
}


// ============================================================================
void Graph::setTimerInterval( int milliseconds )
{
    stopTimer();
    startTimer( milliseconds );
    
    std::cout << std::endl;
    std::cout << "----------------> GRAPH <----------------";
    std::cout << std::endl;
    std::cout << "Timer interval: ";
    std::cout << getTimerInterval();
    std::cout << " ms";
    std::cout << std::endl;
}



void Graph::timerCallback()
{
    if ( mr_analyser.getNextFFTBlockStatus() )
    {
        mr_analyser.drawNextFrameOfSpectrum();
        mr_analyser.setNextFFTBlockStatus( false );
        repaint();
    }
}


// ============================================================================
void Graph::setScaleType( bool isLogarithmic )
{
    m_graphMaximumsLine.setScaleType( isLogarithmic );
    m_graphLine.setScaleType( isLogarithmic );
    m_graphBins.setScaleType( isLogarithmic );
}



void Graph::setGraphStyleAsBins( bool isBins )
{
    if ( isBins == true )
    {
        m_graphLine.setVisible( false );
        m_graphBins.setVisible( true );
    }
    else
    {
        m_graphLine.setVisible( true );
        m_graphBins.setVisible( false );
    }
    
    std::cout << std::endl;
    std::cout << "----------------> GRAPH <----------------";
    std::cout << std::endl;
    std::cout << "Graph style is bins: ";
    std::cout << std::boolalpha << isBins;
    std::cout << std::endl;
}


// ============================================================================
void Graph::maximumVolumesAreShown( bool areShown )
{
    if ( areShown )
    {
        m_graphMaximumsLine.setVisible( true );
    }
    else
    {
        m_graphMaximumsLine.setVisible( false );
    }
    
    std::cout << std::endl;
    std::cout << "----------------> GRAPH <----------------";
    std::cout << std::endl;
    std::cout << "Maximum volumes are shown: ";
    std::cout << std::boolalpha << areShown;
    std::cout << std::endl;
}
