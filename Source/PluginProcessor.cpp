#include "PluginProcessor.h"
#include "PluginEditor.h"

SpectrumAudioProcessor::SpectrumAudioProcessor()
    : AudioProcessor(
#ifndef JucePlugin_PreferredChannelConfigurations
    BusesProperties()
    #if ! JucePlugin_IsMidiEffect
        #if ! JucePlugin_IsSynth
            .withInput( "Input",  juce::AudioChannelSet::stereo(), true )
        #endif
        .withOutput( "Output", juce::AudioChannelSet::stereo(), true )
    #endif
        )
#endif
{
    
}

SpectrumAudioProcessor::~SpectrumAudioProcessor()
{
    
}


// ===========================================================================
const juce::String SpectrumAudioProcessor::getName() const
{
    return JucePlugin_Name;
}



bool SpectrumAudioProcessor::acceptsMidi() const
{
#if JucePlugin_WantsMidiInput
    return true;
#else
    return false;
#endif
}



bool SpectrumAudioProcessor::producesMidi() const
{
#if JucePlugin_ProducesMidiOutput
    return true;
#else
    return false;
#endif
}



bool SpectrumAudioProcessor::isMidiEffect() const
{
#if JucePlugin_IsMidiEffect
    return true;
#else
    return false;
#endif
}


// ===========================================================================
double SpectrumAudioProcessor::getTailLengthSeconds() const { return 0.0; }
int SpectrumAudioProcessor::getNumPrograms() { return 1; }
int SpectrumAudioProcessor::getCurrentProgram() { return 0; }
void SpectrumAudioProcessor::setCurrentProgram( int index ) {}
const juce::String SpectrumAudioProcessor::getProgramName( int index )
{
    return {};
}



void SpectrumAudioProcessor::changeProgramName(
    int index,
    const juce::String &newName ) {}


// ===========================================================================
void SpectrumAudioProcessor::prepareToPlay(
    double sampleRate,
    int samplesPerBlock ) {}



void SpectrumAudioProcessor::processBlock(
    juce::AudioBuffer<float> &buffer,
    juce::MidiBuffer &midiMessages )
{
    if ( 0 < buffer.getNumChannels() )
    {
        auto *leftChannelData = buffer.getReadPointer( 0 );
        auto *rightChannelData = buffer.getReadPointer( 1 );

        for ( auto sample = 0; sample < buffer.getNumSamples(); ++sample )
        {
            m_analyser.pushNextSampleIntoFifo(
                leftChannelData[ sample ],
                rightChannelData[ sample ] );
        }
    }
}



void SpectrumAudioProcessor::releaseResources() {}


#ifndef JucePlugin_PreferredChannelConfigurations
bool SpectrumAudioProcessor::isBusesLayoutSupported(
    const BusesLayout &layouts ) const
{
    #if JucePlugin_IsMidiEffect
        juce::ignoreUnused( layouts );
        return true;
    #else
        // This is the place where you check if the layout is supported.
        // In this template code we only support mono or stereo.
        // Some plugin hosts, such as certain GarageBand versions, will only
        // load plugins that support stereo bus layouts.
        if ( layouts.getMainOutputChannelSet() !=
            juce::AudioChannelSet::mono() &&
            layouts.getMainOutputChannelSet() !=
            juce::AudioChannelSet::stereo() )
        {
            return false;
        }
        // This checks if the input layout matches the output layout
        #if ! JucePlugin_IsSynth
            if ( layouts.getMainOutputChannelSet() !=
                layouts.getMainInputChannelSet() )
            {
                return false;
            }
        #endif
    return true;
    #endif
}
#endif


// ===========================================================================
bool SpectrumAudioProcessor::hasEditor() const { return true; }



juce::AudioProcessorEditor *SpectrumAudioProcessor::createEditor()
{
    return new SpectrumAudioProcessorEditor( *this, m_analyser );
}


// ===========================================================================
void SpectrumAudioProcessor::getStateInformation(
    juce::MemoryBlock &destData ) {}



void SpectrumAudioProcessor::setStateInformation(
    const void *data,
    int sizeInBytes ) {}


// This creates new instances of the plugin... ===============================
juce::AudioProcessor *JUCE_CALLTYPE createPluginFilter()
{
    return new SpectrumAudioProcessor();
}
