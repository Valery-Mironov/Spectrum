#pragma once

#include <JuceHeader.h>
#include "Categories/BlockControl.h"
#include "Categories/ChannelControls.h"
#include "Categories/RefreshControl.h"
#include "Categories/AvgControl.h"
#include "Categories/GraphControls.h"
#include "Categories/ScaleXControls.h"
#include "Categories/ScaleYControls.h"

/*
    TASKS

    Add separators
    Configure the correct display of elements
*/

// ****************************************************************************
// CONTROLS CLASS
// ****************************************************************************
class Controls : public juce::Component
{
public:
    // ========================================================================
    Controls( juce::AudioProcessorValueTreeState & );
    
    
    // ========================================================================
    void resized() override;
    
    
    // ========================================================================
    void setMarginInPixels( int );
    
private:
    // ========================================================================
    juce::Label m_blockLabel;
    juce::Label m_channelLabel;
    juce::Label m_refreshLabel;
    juce::Label m_avgLabel;
    juce::Label m_graphLabel;
    juce::Label m_scaleLabel;
    juce::Label m_rangeLabel;
    
    BlockControl m_blockControl;
    ChannelControls m_channelControls;
    RefreshControl m_refreshControl;
    AvgControl m_avgControl;
    GraphControls m_graphControls;
    ScaleXControls m_scaleXControls;
    ScaleYControls m_scaleYControls;
    
    int m_marginInPixels { 10 };
    
    
    // ========================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR( Controls )
};
