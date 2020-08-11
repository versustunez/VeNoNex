//
// Created by versustune on 2020-02-28.
//

#include "WaveTableOscillator.h"
#include "../../Core/AudioConfig.h"
#include "../../Utils.h"

WaveTableOscillator::WaveTableOscillator() {
    baseWaveGroup = WaveTableGenerator::getInstance().getGroup(WaveForms::SAW);
    for (auto &voice : voices) {
        voice = new Voice();
    }
}

void
WaveTableOscillator::setFreq(float freq, int unisonVoices, float detuneAmp, float detuneDensity, int midiNote) {
    setFreqForVoice(currentMainVoice, freq);
    if (unisonVoices > 0) {
        detuneLookup.setNewLookup(freq, unisonVoices * 2, detuneAmp, detuneDensity, midiNote);
        int length = unisonVoices * 2 + 1;
        for (int i = 0; i < length; i++) {
            if (i == currentMainVoice) {
                continue;
            }
            setFreqForVoice(i, detuneLookup.getCalculatedDetune(i));
        }
    }
}

void WaveTableOscillator::setPhaseOffset(float offset) {
    for (auto &voice : voices) {
        voice->mPhaseOfs = offset;
    }
}

void WaveTableOscillator::updatePhase(int voice) {
    auto cVoice = voices[voice];
    cVoice->mPhasor += cVoice->mPhaseInc;
    if (cVoice->mPhasor >= 1.0)
        cVoice->mPhasor -= 1.0;
}

float WaveTableOscillator::getOutput(int voice) {
    auto cVoice = voices[voice];
    if (cVoice->mPhaseOfs > 0) {
        return getOutputPWM(voice) * detuneBalance[voice];
    }
    return getOutputRaw(voice, 0) * detuneBalance[voice];
}

void WaveTableOscillator::setFreqForVoice(int voice, float freq) {
    // if currentWaveGroup == nullptr and the setting is not success return!
    if (currentWaveGroup == nullptr && setWaveTable(WaveForms::SAW)) {
        return;
    }
    float inc = freq / AudioConfig::getInstance()->getSampleRate();
    auto currentVoice = voices[voice];
    //something is complete wrong!
    if (currentVoice == nullptr) {
        return;
    }
    currentVoice->mPhaseInc = inc;
    if (voice == currentMainVoice) {
        int curWaveTable = 0;
        while ((curWaveTable < (currentWaveGroup->m_numWaveTables - 1) && 
               (inc >= currentWaveGroup->m_WaveTables[curWaveTable]->m_topFreq))) {
            ++curWaveTable;
        }
        currentVoice->currentWaveTable = currentWaveGroup->m_WaveTables[curWaveTable];

        if (currentWaveGroup != baseWaveGroup) {
            curWaveTable = 0;
            while ((curWaveTable < (baseWaveGroup->m_numWaveTables - 1) && 
                  (inc >= baseWaveGroup->m_WaveTables[curWaveTable]->m_topFreq))) {
                ++curWaveTable;
            }
        }
        currentVoice->baseWaveTable = baseWaveGroup->m_WaveTables[curWaveTable];
    } else {
        currentVoice->currentWaveTable = voices[currentMainVoice]->currentWaveTable;
        currentVoice->baseWaveTable = voices[currentMainVoice]->baseWaveTable;
    }
}

float WaveTableOscillator::getOutputRaw(int voice, float phaseOffset) {
    auto cVoice = voices[voice];
    if (cVoice->baseWaveTable != nullptr) {
        float phase = (float) cVoice->mPhasor + phaseOffset;
        auto sum = getOutputForPhaseAndWaveTable(cVoice->baseWaveTable, phase);
        auto finalSum = getOutputForPhaseAndWaveTable(cVoice->currentWaveTable, phase);
        return mixTables(sum, finalSum);
    }
    return 0;
}

float WaveTableOscillator::getOutputPWM(int voice) {
    auto offset = voices[voice]->mPhaseOfs;
    float sumOne = getOutputRaw(voice, 0);
    float sumTwo = getOutputRaw(voice, offset);
    return VeNo::Utils::clamp((sumOne + sumTwo) / 2, -1, 1);
}

float WaveTableOscillator::mixTables(float base, float second) {
    float diff = 1 - waveTableMix;
    base *= diff;
    second *= waveTableMix;
    return VeNo::Utils::clamp(base + second, -1, 1);
}

bool WaveTableOscillator::setWaveTable(int table) {
    baseWaveGroup = WaveTableGenerator::getInstance().getGroup(WaveForms::SAW);
    currentWaveGroup = WaveTableGenerator::getInstance().getGroup(table);
    isSineMode = table == WaveForms::SINE;
    return currentWaveGroup == nullptr || baseWaveGroup == nullptr;
}

float WaveTableOscillator::getOutputForPhaseAndWaveTable(WaveTableObject *table, float phase) {
    if (table == nullptr) {
        return 0.0;
    }
    if (phase > 1.0) {
        phase -= 1.0;
    }
    float val = phase * (float) table->m_waveTableLen;
    int value = (int) val;
    int temp = (int) val + 1;
    if (temp > table->m_waveTableLen) {
        temp -= table->m_waveTableLen;
    }
    float sum = table->m_waveTable[value];
    float sum2 = table->m_waveTable[temp];

    float fraction = val - (float) value;
    float finalSum = sum + fraction * (sum2 - sum);
    return finalSum;
}

void WaveTableOscillator::reset() {
    for (auto &voice : voices) {
        voice->mPhasor = 0;
    }
}
