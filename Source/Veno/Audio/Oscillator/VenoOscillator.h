//
// Created by maurice on 27.09.19.
//

#ifndef VENO_VENOOSCILLATOR_H
#define VENO_VENOOSCILLATOR_H

#include "VenoEnvelope.h"
#include "cmath"
#include "string"
#include "memory"
#include "Modules/WideningModule.h"
#include "Modules/FilterModule.h"
#include "Modules/LimiterModule.h"
#include "Modules/Vibrato.h"
#include "WaveTableOscillator.h"

#define PI 3.141592653589793238462643383
#define PI_4 0.78539816339
#define SQRT2_2 0.70710678118

/**
 * this is the base class from all Oscillator
 * Detune only works with 2 or more Voices
 */
class VenoOscillator {
public:
    VenoOscillator(VenoLFO *vibratoLFO);

    ~VenoOscillator() = default;

    bool render();

    void setup();

    void start(int currentMidiNote);

    void stop();

    void setActive(bool active) {
        VenoOscillator::active = active;
    };

    void setVoices(int voiceCount);

    float getMono() {
        return output[0];
    }

    float getLeft() {
        return output[1];
    }

    float getRight() {
        return output[2];
    }

    void setPhase(float _phase) {
        if (_phase > 1 || _phase < -1) {
            _phase = 0.0;
        }
        VenoOscillator::phase = _phase;
        this->tableHelper.setPhaseOffset(_phase);
    }

    void setPitchBend(float _pitchBend);

    void setSemitonesShift(int semitonesShift);

    void setPanning(float panning);

    void setReTrigger(bool reTrigger);

    void setLevel(float level);

    void setWaveForm(int waveForm);
    void setDetune(float detune);

    void setPitchBendRange(int up, int down);
    void setPitchBendRangeUp(int up);
    void setPitchBendRangeDown(int down);

    std::string name = "osc0";
    float detuneDensity = 0; //shifting doom

    WaveTableOscillator tableHelper;
    // Modules
    VenoWidenessModule widenessModule;
    VenoFilterModule filter;
    VenoLimiterModule limiterModule;
    VenoVibratoModule vibratoModule;
protected:

    void applyPanning() {
        float mono = output[0];
        output[1] = (panning[0] * (mono + panned[0]));
        output[2] = (panning[1] * (mono + panned[1]));
    }

    float getFrequencyFromMidiNote();//is a little bit advance because we want to use detune here
private:
    //gui
    bool reTrigger = false;
    bool active = false;
    bool dualMode = false;

    int semitonesShift = 0;
    int pitchBend = 0; // between -100 and 100
    int pitchBendRange[2] = {12,12};
    int voices = 1;
    int waveForm = WaveForms::SAW;

    float phase = 0;
    float level = 1;
    float panning[2] = {SQRT2_2, SQRT2_2};
    float detune = 0.0;
    float prevDetune = 0.0; // mapped to gui... is not the real value

    //base
    double midiNote;
    int maxVoices = 9;
    float output[3] = {0, 0, 0};
    float panned[2] = {0, 0};
};

#undef PI
#endif //VENO_VENOOSCILLATOR_H
