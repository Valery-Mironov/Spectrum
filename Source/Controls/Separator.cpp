#include <JuceHeader.h>
#include "Separator.h"

Separator::Separator() {}
Separator::~Separator() {}


// ============================================================================
void Separator::paint( juce::Graphics &g )
{
    g.setColour( m_lineColour );
    g.drawLine( 0, getHeight() / 2, getWidth(), getHeight() / 2 );
}



void Separator::resized() {}
