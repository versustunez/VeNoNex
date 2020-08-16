#include "PluginProcessor.h"
#include "PluginEditor.h"

VenoAudioProcessor::VenoAudioProcessor()
        : AudioProcessor(BusesProperties().withOutput("Output", AudioChannelSet::stereo(), true)),
          m_id(Uuid().toString().toStdString()),
          treeState(*this, nullptr, "VeNo", VenoInstance::getInstance(m_id)->handler->setupProcessor())
{
    instance = VenoInstance::getInstance(m_id);
    instance->handler->initParameterForListener(&treeState);
    AudioConfig::registerInstance(m_id);
}

VenoAudioProcessor::~VenoAudioProcessor()
{
    m_synth.removeSound(0);
    for (int i = 0; i < 5; ++i)
    {
        m_synth.removeVoice(i);
    }
    AudioConfig::deleteInstance(m_id);
    VenoInstance::deleteInstance(m_id);
    instance.reset();
}

const String VenoAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool VenoAudioProcessor::acceptsMidi() const
{
    return true;
}

bool VenoAudioProcessor::producesMidi() const
{
    return false;
}

bool VenoAudioProcessor::isMidiEffect() const
{
    return false;
}

double VenoAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int VenoAudioProcessor::getNumPrograms()
{
    return 1;
}

int VenoAudioProcessor::getCurrentProgram()
{
    return 0;
}

void VenoAudioProcessor::setCurrentProgram(int index)
{
}

const String VenoAudioProcessor::getProgramName(int index)
{
    return {};
}

void VenoAudioProcessor::changeProgramName(int index, const String& newName)
{
}

//==============================================================================
void VenoAudioProcessor::prepareToPlay(double sampleRate, int samplesPerBlock)
{
    DBG("SampleRate: " << sampleRate);
    AudioConfig::getInstance()->setSampleRate(sampleRate);
    m_synth.setCurrentPlaybackSampleRate(sampleRate);
    if (!m_isInit)
    {
        for (int p = 0; p < 5; p++)
        {
            m_synth.addVoice(new VenoVoice(p, sampleRate));
        }
        m_synth.addSound(new VenoSound());
        m_isInit = true;
    }
}

void VenoAudioProcessor::releaseResources()
{
}

#ifndef JucePlugin_PreferredChannelConfigurations

bool VenoAudioProcessor::isBusesLayoutSupported(const BusesLayout& layouts) const
{
#if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
#else
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
        && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
        return false;
#if !JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
#endif
    return true;
#endif
}

#endif

void VenoAudioProcessor::processBlock(AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    ScopedNoDenormals noDenormals;
    int numChannels = buffer.getNumChannels(), numSamples = buffer.getNumSamples();
    instance->matrix->updateSlots();
    instance->audioBuffer->reset(numSamples);
    if (m_isInit)
    {
        m_synth.renderNextBlock(buffer, midiMessages, 0, numSamples);
        for (int i = 0; i < numChannels; ++i)
        {
            auto c = buffer.getReadPointer(i);
            for (int j = 0; j < numSamples; ++j)
            {
                instance->audioBuffer->addMonoSample(c[j], j);
                if (i == 0)
                {
                    instance->audioBuffer->addLeftSample(c[j], j);
                }
                if (i == 1 || numChannels == 1)
                {
                    instance->audioBuffer->addRightSample(c[j], j);
                }
            }
        }
        instance->audioBuffer->calcPeak();
    }
}

//==============================================================================
bool VenoAudioProcessor::hasEditor() const
{
    return true;
}

AudioProcessorEditor* VenoAudioProcessor::createEditor()
{
    return new VenoAudioProcessorEditor(*this);
}

//==============================================================================
void VenoAudioProcessor::getStateInformation(MemoryBlock& destData)
{
    auto matrixXML = instance->matrix->saveMatrixToXML();
    if (matrixXML != nullptr)
    {
        copyXmlToBinary(*matrixXML, destData);
    }
    else
    {
        DBG("Sorry something went wrong! xml is nullptr");
    }
}

void VenoAudioProcessor::setStateInformation(const void* data, int sizeInBytes)
{
    std::unique_ptr<XmlElement> xmlState(getXmlFromBinary(data, sizeInBytes));
    if (xmlState != nullptr)
        instance->matrix->getMatrixFromXML(xmlState);
}

AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new VenoAudioProcessor();
}