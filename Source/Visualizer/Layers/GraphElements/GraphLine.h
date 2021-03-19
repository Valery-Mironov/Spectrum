#pragma once

#include <JuceHeader.h>
#include "../../Analyser.h"

// ****************************************************************************
// GRAPH LINE CLASS
// ****************************************************************************
class GraphLine : public juce::Component
{
public:
    GraphLine( Analyser &a );
    ~GraphLine() override;
    
    
    // ========================================================================
    void paint( juce::Graphics &g ) override;
    void resized() override;
    
    
    // ========================================================================
    void setScaleType( bool isLogarithmic );
    
protected:
    // ========================================================================
    template<class Type>
    float normalizeValue( Type T );
    virtual float getScopeDataFromAnalyser( size_t index );
    virtual void drawFrame( juce::Graphics &g );
    
    
    // ========================================================================
    Analyser &mr_analyser;
    bool m_isLogarithmicScale { true };
    
    
    // ========================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR( GraphLine )
};
