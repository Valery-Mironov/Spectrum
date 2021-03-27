#pragma once

#include <JuceHeader.h>
#include "../../Analyser.h"

// ****************************************************************************
// GRAPH LINE CLASS
// ****************************************************************************
class GraphLine : public juce::Component
{
public:
    GraphLine( Analyser & );
    ~GraphLine() override;
    
    
    // ========================================================================
    void paint( juce::Graphics & ) override;
    
    
    // ========================================================================
    void setScaleType( bool );
    virtual void setColour( const juce::Colour & );
    
protected:
    // ========================================================================
    template<class Type>
    float normalizeValue( Type );
    virtual float getScopeDataFromAnalyser( size_t );
    virtual void drawFrame( juce::Graphics & );
    
    
    // ========================================================================
    Analyser &mr_analyser;
    std::atomic<bool> m_isLogarithmicScale { true };
    juce::Colour m_colour { 0x0048bde8 };
    
    
    // ========================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR( GraphLine )
};
