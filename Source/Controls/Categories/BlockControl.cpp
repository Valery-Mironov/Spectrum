#include "BlockControl.h"

// ****************************************************************************
// BLOCK CONTROL CLASS
// ****************************************************************************
BlockControl::BlockControl(
    juce::AudioProcessorValueTreeState &audioProcessorValueTreeState
) :
    mr_audioProcessorValueTreeState( audioProcessorValueTreeState )
{
    addAndMakeVisible( m_blockComboBox );
    m_blockComboBox.addItem( "2048", 11 );
    m_blockComboBox.addItem( "4096", 12 );
    m_blockComboBox.addItem( "8192", 13 );
    m_blockComboBox.addItem( "16384", 14 );
    m_blockComboBox.setSelectedId( 11, juce::dontSendNotification );
    
    m_blockComboBoxAttachment =
        std::make_unique<Attachment>(
            mr_audioProcessorValueTreeState,
            "BLOCK_ID",
            m_blockComboBox
        );
}



BlockControl::~BlockControl() {}


// ============================================================================
void BlockControl::resized()
{
    m_blockComboBox.setBounds( getLocalBounds() );
}
