#include <JuceHeader.h>
#include "Curve.h"


// ****************************************************************************
// CURVE CLASS
// ****************************************************************************
Curve::Curve( Analyser &a ) : mr_analyser( a )
{
    startTimer( 60 );
}



Curve::~Curve()
{
    stopTimer();
}


// ============================================================================
void Curve::paint( juce::Graphics &g )
{
    g.setColour( juce::Colours::white );
    drawFrame( g );
}



void Curve::resized()
{
    
}


// ============================================================================
void Curve::timerCallback()
{
    if ( mr_analyser.getNextFFTBlockStatus() )
    {
        mr_analyser.drawNextFrameOfSpectrum();
        mr_analyser.setNextFFTBlockStatus( false );
        repaint();
    }
}



void Curve::setScaleType( bool isLogarithmicScale )
{
    logarithmicScale = isLogarithmicScale;
}


// ========================================================================
template<class Type>
float Curve::normalizeValue( Type T )
{
    if ( logarithmicScale )
    {
        return
            std::log10f( static_cast<float>( T ) / mr_analyser.getOffset() );
    }
    else
    {
        return static_cast<float>( T );
    }
}


// ============================================================================
void Curve::drawFrame( juce::Graphics &g )
{
    auto width  = static_cast<float>( getLocalBounds().getWidth() );
    auto height = static_cast<float>( getLocalBounds().getHeight() );
    
    juce::Path curve;
    
    curve.startNewSubPath(
        0.0f,
        juce::jmap(
            mr_analyser.getScopeData( 0 ),
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
                    mr_analyser.getScopeData( x ),
                    0.0f,
                    1.0f,
                    height,
                    0.0f )
            } );
    }
    
    g.strokePath(
        curve.createPathWithRoundedCorners( 1.0f ),
        juce::PathStrokeType( 1.0f ) );
}
