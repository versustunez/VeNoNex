//
// Created by versustune on 2020-02-28.
//

#ifndef VENO_WAVETABLEOSCILLATOR_H
#define VENO_WAVETABLEOSCILLATOR_H


#include "../WaveTable/WaveTableGenerator.h"
#include "DetuneLookup.h"

struct Voice {
    double mPhasor = 0.0;
    double mPhaseInc = 0.0;
    double mPhaseOfs = 0;
    WaveTableObject *baseWaveTable = nullptr;
    WaveTableObject *currentWaveTable = nullptr;
};

class WaveTableOscillator {
private:
    WaveTableGroup *baseWaveGroup = nullptr;
    WaveTableGroup *currentWaveGroup = nullptr;
    static constexpr int voiceCount = 9;
    Voice *voices[voiceCount] = {};
    float detuneBalance[9] = {0.9994299170182994, 0.9986636836409448, 1.0040088043085003, 0.9964991290729566,
                              1, 1.0005758205730941,
                              0.9963415939105666, 0.9962643415328123, 1.0005062539081053};
    bool isSineMode = false;
public:
    WaveTableOscillator();

    ~WaveTableOscillator() = default;

    void setFreq(float freq, int unisonVoices, float detuneAmp, float detuneDensity, int midiNote);

    bool setWaveTable(int table);

    void setPhaseOffset(float offset);

    void updatePhase(int voice);

    float getOutput(int voice);

    void reset();

    // number between 0 and 1
    float waveTableMix = 0;
    DetuneLookup detuneLookup = {};
    int currentMainVoice = 0;
protected:
    void setFreqForVoice(int voice, float freq);

    float getOutputPWM(int voice);

    float mixTables(float base, float second);

    float getOutputForPhaseAndWaveTable(WaveTableObject *table, float phase);

    float getOutputRaw(int voice, float phaseOffset);
};


#endif //VENO_WAVETABLEOSCILLATOR_H
