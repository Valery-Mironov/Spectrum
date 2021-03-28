#include "GraphMaximumsLine.h"

GraphMaximumsLine::GraphMaximumsLine(
    Analyser &analyser
) :
    GraphLine::GraphLine( analyser ) {}



GraphMaximumsLine::~GraphMaximumsLine() {}


// ============================================================================
float GraphMaximumsLine::getScopeDataFromAnalyser( const size_t index )
{
    return mr_analyser.getScopeMaximumsData( index );
}
