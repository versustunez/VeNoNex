#pragma once

#include <JuceHeader.h>
#include "Veno/VenoInstance.h"

class VenoAudioProcessor : public AudioProcessor
{
public:
    //==============================================================================
    VenoAudioProcessor ();
    ~VenoAudioProcessor ();
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources () override;
#ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
#endif
    void processBlock (AudioBuffer<float>&, MidiBuffer&) override;
    AudioProcessorEditor* createEditor () override;
    bool hasEditor () const override;
    const String getName () const override;
    bool acceptsMidi () const override;
    bool producesMidi () const override;
    bool isMidiEffect () const override;
    double getTailLengthSeconds () const override;
    int getNumPrograms () override;
    int getCurrentProgram () override;
    void setCurrentProgram (int index) override;
    const String getProgramName (int index) override;
    void changeProgramName (int index, const String& newName) override;
    void getStateInformation (MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;
    // Variable to communicate with the GUI and the Processor
    std::string m_id = Uuid().toString().toStdString();
    std::shared_ptr<VenoInstance> instance;
private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (VenoAudioProcessor)
};
