#pragma once

#include <JuceHeader.h>
#include "../Visualizer/Analyser.h"

// ****************************************************************************
// CONTROLS CLASS
// ****************************************************************************
class Controls : public juce::Component
{
public:
    Controls( Analyser &a );
    ~Controls() override;
    
    
    // ========================================================================
    void paint( juce::Graphics &g ) override;
    void resized() override;
    
private:
    // ========================================================================
    Analyser &mr_analyser;
    
    juce::Label m_blockLabel;
    juce::ComboBox m_blockComboBox;
    
    juce::Label m_channelLabel;
    juce::TextButton m_leftTextButton;
    juce::TextButton m_rightTextButton;
    juce::TextButton m_leftPlusRightTextButton;
    
    juce::Label m_refreshLabel;
    juce::Slider m_refreshSlider;
    
    juce::Label m_avgLabel;
    juce::Slider m_avgSlider;
    
    juce::Label m_graphLabel;
    juce::TextButton m_lineTextButon;
    juce::TextButton m_maxTextButton;
    
    juce::Label m_scaleLabel;
    juce::TextButton m_linTextButton;
    juce::TextButton m_logTextButton;
    juce::TextButton m_stTextButton;
    
    juce::TextButton m_rangeTextButton;
    juce::Slider m_minimumVolumeSlider;
    juce::Slider m_maximumVolumeSlider;
    
    // Должен устанавливатсья 'set' методом
    static constexpr double m_marginInPixels { 10 };
    
    
    // ========================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR( Controls )
};
