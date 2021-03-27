#include "PluginProcessor.h"
#include "PluginEditor.h"

SpectrumAudioProcessor::SpectrumAudioProcessor() :
    AudioProcessor(
        BusesProperties()
            .withInput( "Input",  juce::AudioChannelSet::stereo(), true )
            .withOutput( "Output", juce::AudioChannelSet::stereo(), true )
        ),
    m_audioProcessorValueTreeState(
        *this,
        nullptr,
        "Parameters",
        createParameters()
    ),
    m_analyser( m_audioProcessorValueTreeState ) {}



SpectrumAudioProcessor::~SpectrumAudioProcessor() {}


// ===========================================================================
const juce::String SpectrumAudioProcessor::getName() const
{
    return JucePlugin_Name;
}



bool SpectrumAudioProcessor::acceptsMidi() const { return false; }
bool SpectrumAudioProcessor::producesMidi() const { return false; }
bool SpectrumAudioProcessor::isMidiEffect() const { return false; }


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
            m_analyser.pushSamplesIntoFifo(
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
        if (
            layouts.getMainOutputChannelSet() !=
            juce::AudioChannelSet::mono() &&
            layouts.getMainOutputChannelSet() !=
            juce::AudioChannelSet::stereo()
        ) {
            return false;
        }
        // This checks if the input layout matches the output layout
        #if ! JucePlugin_IsSynth
            if (
                layouts.getMainOutputChannelSet() !=
                layouts.getMainInputChannelSet()
            ) {
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
    return new
        SpectrumAudioProcessorEditor(
            *this,
            m_audioProcessorValueTreeState,
            m_analyser
        );
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


// ============================================================================
juce::AudioProcessorValueTreeState::ParameterLayout SpectrumAudioProcessor::createParameters()
{
    std::vector<std::unique_ptr<juce::RangedAudioParameter>> parameters;
    // ------------------------------------------------------------------------
    juce::StringArray choices = { "2048", "4096", "8192", "16384" };
    
    parameters.push_back(
        std::make_unique<juce::AudioParameterChoice>(
            "BLOCK_ID",
            "Block",
            choices,
            0
        )
    );
    // ------------------------------------------------------------------------
    parameters.push_back(
        std::make_unique<juce::AudioParameterBool>(
            "LEFT_ID",
            "Left",
            false
        )
    );
    
    parameters.push_back(
        std::make_unique<juce::AudioParameterBool>(
            "RIGHT_ID",
            "Right",
            false
        )
    );
    
    parameters.push_back(
        std::make_unique<juce::AudioParameterBool>(
            "BOTH_ID",
            "Both",
            true
        )
    );
    // ------------------------------------------------------------------------
    parameters.push_back(
        std::make_unique<juce::AudioParameterInt>(
            "REFRESH_ID",
            "Refresh",
            40,
            200,
            60
        )
    );
    // ------------------------------------------------------------------------
    parameters.push_back(
        std::make_unique<juce::AudioParameterInt>(
            "AVG_ID",
            "Avg",
            1,
            8,
            1
        )
    );
    // ------------------------------------------------------------------------
    parameters.push_back(
        std::make_unique<juce::AudioParameterBool>(
            "BINS_ID",
            "Bins",
            true
        )
    );
    
    parameters.push_back(
        std::make_unique<juce::AudioParameterBool>(
            "MAX_ID",
            "Max",
            true
        )
    );
    // ------------------------------------------------------------------------
    parameters.push_back(
        std::make_unique<juce::AudioParameterBool>(
            "LIN_ID",
            "Lin",
            false
        )
    );
    
    parameters.push_back(
        std::make_unique<juce::AudioParameterBool>(
            "LOG_ID",
            "Log",
            true
        )
    );
    
    parameters.push_back(
        std::make_unique<juce::AudioParameterBool>(
            "ST_ID",
            "ST",
            false
        )
    );
    // ------------------------------------------------------------------------
    parameters.push_back(
        std::make_unique<juce::AudioParameterBool>(
            "RANGE_ID",
            "Range",
            true
        )
    );
    
    parameters.push_back(
        std::make_unique<juce::AudioParameterInt>(
            "MAXIMUM_ID",
            "Maximum",
            -200,
            40,
            12
        )
    );
    
    parameters.push_back(
        std::make_unique<juce::AudioParameterInt>(
            "MINIMUM_ID",
            "Minimum",
            -380,
            30,
            -120
        )
    );
        
    return { parameters.begin(), parameters.end() };
}
