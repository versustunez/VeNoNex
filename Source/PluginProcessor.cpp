#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "Veno/Core/AudioConfig.h"

VenoAudioProcessor::VenoAudioProcessor ()
/*#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif*/
        : AudioProcessor (BusesProperties ().withInput ("Input", AudioChannelSet::stereo (), true).withOutput ("Output",
                                                                                                               AudioChannelSet::stereo (),
                                                                                                               true))
{
    instance = VenoInstance::createInstance (m_id);
}

VenoAudioProcessor::~VenoAudioProcessor ()
{
    VenoInstance::deleteInstance (m_id);
}

const String VenoAudioProcessor::getName () const
{
    return JucePlugin_Name;
}

bool VenoAudioProcessor::acceptsMidi () const
{
#if JucePlugin_WantsMidiInput
    return true;
#else
    return false;
#endif
}

bool VenoAudioProcessor::producesMidi () const
{
#if JucePlugin_ProducesMidiOutput
    return true;
#else
    return false;
#endif
}

bool VenoAudioProcessor::isMidiEffect () const
{
#if JucePlugin_IsMidiEffect
    return true;
#else
    return false;
#endif
}

double VenoAudioProcessor::getTailLengthSeconds () const
{
    return 0.0;
}

int VenoAudioProcessor::getNumPrograms ()
{
    return 1;
}

int VenoAudioProcessor::getCurrentProgram ()
{
    return 0;
}

void VenoAudioProcessor::setCurrentProgram (int index)
{
}

const String VenoAudioProcessor::getProgramName (int index)
{
    return {};
}

void VenoAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void VenoAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    auto audioConfig = AudioConfig::getInstance ();
    audioConfig->setSampleRate (sampleRate);
    audioConfig->initWaveTables ();
}

void VenoAudioProcessor::releaseResources ()
{
}

#ifndef JucePlugin_PreferredChannelConfigurations

bool VenoAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
#if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
#else
    if (layouts.getMainOutputChannelSet () != AudioChannelSet::mono ()
        && layouts.getMainOutputChannelSet () != AudioChannelSet::stereo ())
        return false;
#if !JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
#endif
    return true;
#endif
}

#endif

void VenoAudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    ScopedNoDenormals noDenormals;
    instance->matrix.updateSlots ();
    instance->audioBuffer->reset (buffer.getNumSamples ());
    int numChannels = buffer.getNumChannels ();
    for (int i = 0; i < numChannels; ++i)
    {
        auto c = buffer.getReadPointer (i);
        for (int j = 0; j < buffer.getNumSamples (); ++j)
        {
            instance->fft.pushNextSampleIntoFifo (c[j]);
            instance->audioBuffer->addMonoSample (c[j], j);
            if (i == 0)
            {
                instance->audioBuffer->addLeftSample (c[j], j);
            }
            if (i == 1 || numChannels == 1)
            {
                instance->audioBuffer->addRightSample (c[j], j);
            }
        }
    }
}

//==============================================================================
bool VenoAudioProcessor::hasEditor () const
{
    return true;
}

AudioProcessorEditor* VenoAudioProcessor::createEditor ()
{
    return new VenoAudioProcessorEditor (*this);
}

//==============================================================================
void VenoAudioProcessor::getStateInformation (MemoryBlock& destData)
{
}

void VenoAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
}

AudioProcessor* JUCE_CALLTYPE createPluginFilter ()
{
    return new VenoAudioProcessor ();
}
