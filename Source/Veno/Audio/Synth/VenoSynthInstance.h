//
// Created by Maurice on 26.09.2019.
//

/*
* VenoSynthInstance save all stuff that is needed for the Synth to work => OSC, ENV and other stuff
*/

#ifndef VENO_VENOSYNTHINSTANCE_H
#define VENO_VENOSYNTHINSTANCE_H


#include "../Oscillator/VenoOscillator.h"
#include "../Oscillator/VenoEnvelope.h"
// #include "../FXChain/Chain.h"

class VenoSynthInstance {
public:
	int index = 0;
	VenoSynthInstance(double sampleRate);
	~VenoSynthInstance();

	//i want that the VenoSynthInstance contains all Oscillatoren
    VenoOscillator *getOscillator(int i) {
	    return oscillators[i];
	}
    VenoEnvelope *getEnvelope(int i) {
        return envelopes[i];
    }
    int count = 4;
    bool isInit = false;
    VenoLFO *vibrato = {};
    void updateSampleRate();
    // void setChain(std::shared_ptr<Chain>& chainModule);

    // std::shared_ptr<Chain> getChain();

private:
    VenoOscillator *oscillators[4];
    VenoEnvelope *envelopes[4];
    // 2 free oscillator and one for vibrato...
    VenoLFO *lfos[2]{};
    float lastSampleRate = 0;
    // std::shared_ptr<Chain> chain;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (VenoSynthInstance)
};


#endif //VENO_VENOSYNTHINSTANCE_H
