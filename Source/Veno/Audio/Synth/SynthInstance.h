#ifndef VENO_SYNTHINSTANCE_H
#define VENO_SYNTHINSTANCE_H

#include <string>
#include "JuceHeader.h"

// class that hold all voices, oscillators and other stuff :)
class SynthInstance
{
private:
    std::string m_processId;
    Synthesiser m_synth;
    double m_sampleRate = -1;
    bool m_isInit = false;
public:
    explicit SynthInstance (std::string processId);
    ~SynthInstance ();

    void render (AudioBuffer<float>& buffer, const MidiBuffer& midiMessages, int startSample, int numSamples);
    void setSampleRate(double sampleRate);
    bool isInit() const;

    void noteOn (int i, int i1, float d);
    void noteOff (int i, int i1, float d);

protected:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SynthInstance)
};

#endif //VENO_SYNTHINSTANCE_H
