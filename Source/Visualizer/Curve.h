#pragma once

#include <JuceHeader.h>
#include "Analyser.h"

// ****************************************************************************
// CURVE CLASS
// ****************************************************************************
class Curve :
    public juce::Component,
    private juce::Timer
{
public:
    Curve( Analyser &a );
    ~Curve() override;
    
    
    // ========================================================================
    void paint( juce::Graphics &g ) override;
    void resized() override;
    
    
    // ========================================================================
    void timerCallback() override;
    void setScaleType( bool isLogarithmicScale );
    
private:
    // ========================================================================
    template<class Type>
    float normalizeValue( Type T );
    void drawFrame( juce::Graphics &g );
    
    
    // ========================================================================
    Analyser &mr_analyser;
    bool logarithmicScale { true };
    
    // ========================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR( Curve )
};
