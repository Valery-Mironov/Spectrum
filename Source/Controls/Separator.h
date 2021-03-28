#pragma once

#include <JuceHeader.h>

// ****************************************************************************
// SEPARATOR CLASS
// ****************************************************************************
class Separator : public juce::Component
{
public:
    Separator();
    ~Separator() override;
    
    
    // ========================================================================
    void paint( juce::Graphics & )override;
    void resized() override;

private:
    // ========================================================================
    juce::Colour m_lineColour { juce::Colour( 0xff969696 ) };
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR( Separator )
};
