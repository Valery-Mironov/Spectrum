#include "GraphBins.h"

GraphBins::GraphBins( Analyser &analyser ) : GraphLine::GraphLine( analyser ) {}
GraphBins::~GraphBins() {}

// ============================================================================
void GraphBins::drawFrame( juce::Graphics &g )
{
    auto width  = static_cast<float>( getLocalBounds().getWidth() );
    auto height = static_cast<float>( getLocalBounds().getHeight() );
    
    for ( int x { 0 }; x < mr_analyser.getScopeSize(); ++x )
    {
        auto xPosition =
            juce::jmap(
                normalizeValue( x ),
                0.0f,
                normalizeValue( mr_analyser.getScopeSize() - 1 ),
                0.0f,
                width
            );
                
        g.drawLine(
            xPosition,
            juce::jmap(
                getScopeDataFromAnalyser( x ),
                1.0f,
                0.0f,
                0.0f,
                height
            ),
            xPosition,
            height,
            1.0f
        );
    }
}
