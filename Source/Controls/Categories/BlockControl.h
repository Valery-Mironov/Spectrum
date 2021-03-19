#pragma once

#include <JuceHeader.h>
#include "../../Visualizer/Analyser.h"

// ****************************************************************************
// BLOCK CONTROL CLASS
// ****************************************************************************
class BlockControl : public juce::Component
{
public:
    BlockControl( Analyser &a );
    ~BlockControl() override;
    
    
    // ========================================================================
    void paint( juce::Graphics &g ) override;
    void resized() override;

private:
    // ========================================================================
    Analyser &mr_analyser;
    
    juce::ComboBox m_blockComboBox;
    
    
    // ========================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR( BlockControl )
};
