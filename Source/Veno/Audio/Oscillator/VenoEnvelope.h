#pragma once
#ifndef VENO_VENOENVELOPE_H
#define VENO_VENOENVELOPE_H

#include "JuceHeader.h"
#include "../Engine/Modulator.h"

/*
 * this is a small wrapper around JUCE ADSR with saving of the current state
 */
class VenoEnvelope : public Modulator {
public:
    VenoEnvelope(double sampleRate);
    ~VenoEnvelope() = default;
    void setAttack(float attack);
    void setRelease(float release);
    void setSustain(float sustain);
    void setDecay(float decay);
    void setSampleRate(float sampleRate);
    float getValue();
    bool isActive();
    void noteOn();
    void noteOff();
    bool reTrigger = false;
    std::string name;
    void update() override;
protected:
    ADSR::Parameters parameters {};
    ADSR adsr;
    double m_sampleRate = 44100;
};

#endif //VENO_VENOENVELOPE_H
