#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "Veno/Core/AudioConfig.h"

VenoAudioProcessor::VenoAudioProcessor ()
        : AudioProcessor (BusesProperties ().withOutput ("Output", AudioChannelSet::stereo (), true)),
          m_id (Uuid ().toString ().toStdString ()),
          instance (VenoInstance::getInstance (m_id)),
          treeState (*this, nullptr, "VeNo", instance->handler->setupProcessor ())
{
    instance->handler->initParameterForListener (&treeState);
    instance->treeState = &treeState;
    instance->modulators->init ();
    AudioConfig::registerInstance (m_id);
}

VenoAudioProcessor::~VenoAudioProcessor ()
{
    instance.reset ();
    AudioConfig::deleteInstance (m_id);
    VenoInstance::deleteInstance (m_id);
}

const String VenoAudioProcessor::getName () const
{
    return JucePlugin_Name;
}

bool VenoAudioProcessor::acceptsMidi () const
{
    return true;
}

bool VenoAudioProcessor::producesMidi () const
{
    return false;
}

bool VenoAudioProcessor::isMidiEffect () const
{
    return false;
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
    AudioConfig::getInstance ()->setSampleRate (sampleRate);
    instance->getSynthInstance()->setSampleRate(sampleRate);
    instance->modulators->updateSampleRate(sampleRate);
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
    int numSamples = buffer.getNumSamples ();
    instance->audioBuffer->reset (numSamples);
    instance->getSynthInstance ()->render (buffer, midiMessages, 0, numSamples);
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
    copyXmlToBinary (*instance->presetManager->getCurrentData (), destData);
}

void VenoAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    std::unique_ptr<XmlElement> xmlState (getXmlFromBinary (data, sizeInBytes));
    if (xmlState != nullptr)
    {
        instance->presetManager->setCurrentData (xmlState);
    }
}

AudioProcessor* JUCE_CALLTYPE createPluginFilter ()
{
    return new VenoAudioProcessor ();
}