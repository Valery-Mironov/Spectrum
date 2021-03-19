#include "BlockControl.h"

// ****************************************************************************
// BLOCK CONTROL CLASS
// ****************************************************************************
BlockControl::BlockControl( Analyser &a ) : mr_analyser( a )
{
    addAndMakeVisible( m_blockComboBox );
    m_blockComboBox.addItem( "2048", 11 );
    m_blockComboBox.addItem( "4096", 12 );
    m_blockComboBox.addItem( "8192", 13 );
    m_blockComboBox.addItem( "16384", 14 );
    m_blockComboBox.setSelectedId(
        11,
        juce::dontSendNotification );
    m_blockComboBox.onChange = [ this ]
    {
        mr_analyser.setFFTBlockSize( m_blockComboBox.getSelectedId() );
    };
}



BlockControl::~BlockControl()
{
    
}


// ============================================================================
void BlockControl::paint( juce::Graphics &g )
{
    
}



void BlockControl::resized()
{
    m_blockComboBox.setBounds( getLocalBounds() );
}
