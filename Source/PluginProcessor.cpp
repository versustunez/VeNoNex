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
    int numChannels = buffer.getNumChannels (), numSamples = buffer.getNumSamples ();
    instance->matrix->updateSlots ();
    instance->audioBuffer->reset (numSamples);
    if (instance->getSynthInstance()->isInit())
    {
        instance->getSynthInstance ()->render (buffer, midiMessages, 0, numSamples);
        buffer.applyGain(instance->handler->getParameterValue("master__volume", 1));
        for (int i = 0; i < numChannels; ++i)
        {
            auto c = buffer.getReadPointer (i);
            for (int j = 0; j < numSamples; ++j)
            {
                instance->audioBuffer->addMonoSample (c[j]);
                if (i == 0)
                {
                    instance->audioBuffer->addLeftSample (c[j]);
                }
                if (i == 1 || numChannels == 1)
                {
                    instance->audioBuffer->addRightSample (c[j]);
                }
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
    auto state = treeState.copyState ();
    std::unique_ptr<XmlElement> xml (state.createXml ());
    copyXmlToBinary (*xml, destData);
/*    auto matrixXML = instance->matrix->saveMatrixToXML ();
    if (matrixXML != nullptr)
    {
        copyXmlToBinary (*matrixXML, destData);
    }
    else
    {
        DBG("Sorry something went wrong! xml is nullptr");
    }*/
}

void VenoAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    std::unique_ptr<XmlElement> xmlState (getXmlFromBinary (data, sizeInBytes));

    if (xmlState != nullptr)
        if (xmlState->hasTagName (treeState.state.getType ()))
            treeState.replaceState (ValueTree::fromXml (*xmlState));
/*    std::unique_ptr<XmlElement> xmlState (getXmlFromBinary (data, sizeInBytes));
    if (xmlState != nullptr)
        instance->matrix->getMatrixFromXML (xmlState);*/
}

AudioProcessor* JUCE_CALLTYPE createPluginFilter ()
{
    return new VenoAudioProcessor ();
}