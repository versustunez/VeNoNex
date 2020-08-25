/*
* VenoSynthInstance save all stuff that is needed for the Synth to work => OSC, ENV and other stuff
*/

#ifndef VENO_VENOSYNTHINSTANCE_H
#define VENO_VENOSYNTHINSTANCE_H


#include "JuceHeader.h"
#include "../Oscillator/VenoEnvelope.h"
#include "../Oscillator/SynthOscillator.h"
// #include "../FXChain/Chain.h"

class VenoSynthInstance
{
public:
    int index = 0;

    VenoSynthInstance (const std::string& id, double sampleRate);

    ~VenoSynthInstance ();

    //i want that the VenoSynthInstance contains all Oscillatoren
    SynthOscillator* getOscillator (int i)
    {
        return oscillators[i];
    }

    VenoEnvelope* getEnvelope (int i)
    {
        return envelopes[i];
    }

    int count = 4;
    bool isInit = false;

    void updateSampleRate ();
    // void setChain(std::shared_ptr<Chain>& chainModule);

    // std::shared_ptr<Chain> getChain();

private:
    SynthOscillator* oscillators[4];
    VenoEnvelope* envelopes[4];
    float lastSampleRate = 0;
    std::string m_id;
    // std::shared_ptr<Chain> chain;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (VenoSynthInstance)
};


#endif //VENO_VENOSYNTHINSTANCE_H
