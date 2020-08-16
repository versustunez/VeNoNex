//
// Created by versustune on 2020-02-28.
//

#ifndef VENO_WAVETABLEOSCILLATOR_H
#define VENO_WAVETABLEOSCILLATOR_H


#include "../WaveTable/WaveTableGenerator.h"
#include "DetuneLookup.h"

struct Voice {
    double m_phasor = 0.0;
    double m_phaseInc = 0.0;
    double m_phaseOfs = 0;
    WaveTableObject *m_baseWaveTable = nullptr;
    WaveTableObject *m_currentWaveTable = nullptr;
};

class WaveTableOscillator {
private:
    WaveTableGroup *m_baseWaveGroup = nullptr;
    WaveTableGroup *m_currentWaveGroup = nullptr;
    static constexpr int voiceCount = 9;
    Voice *m_voices[voiceCount]{};
public:
    WaveTableOscillator();

    ~WaveTableOscillator();

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
