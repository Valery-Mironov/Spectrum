#include "GraphLine.h"

GraphLine::GraphLine( Analyser &analyser ) : mr_analyser( analyser ) {}
GraphLine::~GraphLine() {}


// ============================================================================
void GraphLine::paint( juce::Graphics &g )
{
    g.setColour( juce::Colours::white );
    drawFrame( g );
}



void GraphLine::resized()
{
    
}


// ============================================================================
void GraphLine::setScaleType( bool isLogarithmic )
{
    m_isLogarithmicScale = isLogarithmic;
    
    std::cout << std::endl;
    std::cout << "----------------> CURVE <----------------";
    std::cout << std::endl;
    std::cout << "Is logarithmic scale: ";
    std::cout << std::boolalpha << m_isLogarithmicScale;
    std::cout << std::endl;
}


// ============================================================================
template<class Type>
float GraphLine::normalizeValue( Type T )
{
    if ( T != 0 && m_isLogarithmicScale )
    {
        return
            std::log10f( static_cast<float>( T ) / mr_analyser.getOffset() );
    }
    else
    {
        return static_cast<float>( T );
    }
}


float GraphLine::getScopeDataFromAnalyser( size_t index )
{
    return mr_analyser.getScopeData( index );
}



// ============================================================================
void GraphLine::drawFrame( juce::Graphics &g )
{
    auto width  = static_cast<float>( getLocalBounds().getWidth() );
    auto height = static_cast<float>( getLocalBounds().getHeight() );
    
    juce::Path curve;
    
    curve.startNewSubPath(
        0.0f,
        juce::jmap(
            getScopeDataFromAnalyser( 0 ),
            0.0f,
            1.0f,
            height,
            0.0f ) );
    
    for ( int x { 1 }; x < mr_analyser.getScopeSize(); ++x )
    {
        curve.lineTo(
            {
                // Next point of the line on the abscissa axis
                juce::jmap(
                    normalizeValue( x ),
                    0.0f,
                    normalizeValue( mr_analyser.getScopeSize() - 1 ),
                    0.0f,
                    width ),
                // Next point of the line along the ordinate axis
                juce::jmap(
                    getScopeDataFromAnalyser( x ),
                    0.0f,
                    1.0f,
                    height,
                    0.0f )
            } );
    }
    
    g.strokePath(
        curve.createPathWithRoundedCorners( 128.0f ),
        juce::PathStrokeType( 1.0f ) );
}
