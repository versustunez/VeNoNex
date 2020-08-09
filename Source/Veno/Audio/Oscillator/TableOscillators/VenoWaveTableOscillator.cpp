//
// Created by versustune on 2020-02-28.
//

#include "VenoWaveTableOscillator.h"

VenoWaveTableOscillator::VenoWaveTableOscillator() {
    baseWaveGroup = VenoWaveTableGenerator::getInstance().getGroup(VenoWaveTableGenerator::SAW);
    for (auto &voice : voices) {
        voice = new Voice();
    }
}

void
VenoWaveTableOscillator::setFreq(float freq, int unisonVoices, float detuneAmp, float detuneDensity, int midiNote) {
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

void VenoWaveTableOscillator::setPhaseOffset(float offset) {
    for (auto &voice : voices) {
        voice->mPhaseOfs = offset;
    }
}

void VenoWaveTableOscillator::updatePhase(int voice) {
    auto cVoice = voices[voice];
    cVoice->mPhasor += cVoice->mPhaseInc;
    if (cVoice->mPhasor >= 1.0)
        cVoice->mPhasor -= 1.0;
}

float VenoWaveTableOscillator::getOutput(int voice) {
    auto cVoice = voices[voice];
    if (cVoice->mPhaseOfs > 0) {
        return getOutputPWM(voice) * detuneBalance[voice];
    }
    return getOutputRaw(voice, 0) * detuneBalance[voice];
}

void VenoWaveTableOscillator::setFreqForVoice(int voice, float freq) {
    if (currentWaveGroup == nullptr) {
        setWaveTable(2);
    }
    float inc = freq / VenoWaveTableGenerator::getInstance().sampleRate;
    auto currentVoice = voices[voice];
    //something is complete wrong!
    if (currentVoice == nullptr) {
        return;
    }
    currentVoice->mPhaseInc = inc;
    if (voice == currentMainVoice) {
        int curWaveTable = 0;
        while ((inc >= currentWaveGroup->mWaveTables[curWaveTable]->topFreq) &&
               (curWaveTable < (currentWaveGroup->numWaveTables - 1))) {
            ++curWaveTable;
        }
        currentVoice->currentWaveTable = currentWaveGroup->mWaveTables[curWaveTable];

        curWaveTable = 0;
        while ((inc >= baseWaveGroup->mWaveTables[curWaveTable]->topFreq) &&
               (curWaveTable < (baseWaveGroup->numWaveTables - 1))) {
            ++curWaveTable;
        }
        currentVoice->baseWaveTable = baseWaveGroup->mWaveTables[curWaveTable];
    } else {
        currentVoice->currentWaveTable = voices[currentMainVoice]->currentWaveTable;
        currentVoice->baseWaveTable = voices[currentMainVoice]->baseWaveTable;
    }
}

float VenoWaveTableOscillator::getOutputRaw(int voice, float phaseOffset) {
    auto cVoice = voices[voice];
    if (cVoice->baseWaveTable != nullptr) {
        float phasor = (float) cVoice->mPhasor + phaseOffset;
        auto sum = getOutputForPhaseAndWaveTable(cVoice->baseWaveTable, phasor);
        auto finalSum = getOutputForPhaseAndWaveTable(cVoice->currentWaveTable, phasor);
        return mixTables(sum, finalSum);
    }
    return 0;
}

float VenoWaveTableOscillator::getOutputPWM(int voice) {
    auto offset = voices[voice]->mPhaseOfs;
    float sumOne = getOutputRaw(voice, 0);
    float sumTwo = getOutputRaw(voice, offset);
    return VenoUtils::clamp((sumOne + sumTwo) / 2, -1, 1);
}

float VenoWaveTableOscillator::mixTables(float base, float second) {
    float diff = 1 - waveTableMix;
    base *= diff;
    second *= waveTableMix;
    return VenoUtils::clamp(base + second, -1, 1);
}

void VenoWaveTableOscillator::setWaveTable(int table) {
    baseWaveGroup = VenoWaveTableGenerator::getInstance().getGroup(VenoWaveTableGenerator::SAW);
    currentWaveGroup = VenoWaveTableGenerator::getInstance().getGroup(table);
    isSineMode = table == VenoWaveTableGenerator::SINE;
}

float VenoWaveTableOscillator::getOutputForPhaseAndWaveTable(WaveTableObject *table, float phase) {
    if (table == nullptr) {
        return 0.0;
    }
    if (phase > 1.0) {
        phase -= 1.0;
    }
    float val = phase * (float) table->waveTableLen;
    int value = (int) val;
    int temp = (int) val;
    if (++temp >= table->waveTableLen) {
        temp = 0;
    }
    float sum = table->waveTable[value];
    float sum2 = table->waveTable[temp];

    float fraction = val - (float) value;
    float finalSum = sum + fraction * (sum2 - sum);
    return finalSum;
}

void VenoWaveTableOscillator::reset() {
    for (auto &voice : voices) {
        voice->mPhasor = 0;
    }
}
