//
// Created by versustune on 2020-02-28.
//

#include "WaveTableOscillator.h"
#include "../../Core/AudioConfig.h"
#include "../../Utils.h"
#include "../../Core/LookupTables.h"

WaveTableOscillator::WaveTableOscillator() {
    m_baseWaveGroup = WaveTableGenerator::getInstance().getGroup(WaveForms::SAW);
    for (auto &voice : m_voices) {
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
    for (auto &voice : m_voices) {
        voice->m_phaseOfs = offset;
    }
}

void WaveTableOscillator::updatePhase(int voice) {
    auto cVoice = m_voices[voice];
    cVoice->m_phasor += cVoice->m_phaseInc;
    if (cVoice->m_phasor >= 1.0)
        cVoice->m_phasor -= 1.0;
}

float WaveTableOscillator::getOutput(int voice) {
    auto cVoice = m_voices[voice];
    if (cVoice->m_phaseOfs > 0) {
        return getOutputPWM(voice) * LookupTables::detuneLookup[voice];
    }
    return getOutputRaw(voice, 0) * LookupTables::detuneLookup[voice];
}

void WaveTableOscillator::setFreqForVoice(int voice, float freq) {
    // if m_currentWaveGroup == nullptr and the setting is not success return!
    if (m_currentWaveGroup == nullptr && setWaveTable(WaveForms::SAW)) {
        return;
    }
    float inc = freq / AudioConfig::getInstance()->getSampleRate();
    auto currentVoice = m_voices[voice];
    //something is complete wrong!
    if (currentVoice == nullptr) {
        return;
    }
    currentVoice->m_phaseInc = inc;
    if (voice == currentMainVoice) {
        int curWaveTable = 0;
        while ((curWaveTable < (m_currentWaveGroup->m_numWaveTables - 1) &&
                (inc >= m_currentWaveGroup->m_WaveTables[curWaveTable]->m_topFreq))) {
            ++curWaveTable;
        }
        currentVoice->m_currentWaveTable = m_currentWaveGroup->m_WaveTables[curWaveTable];

        if (m_currentWaveGroup != m_baseWaveGroup) {
            curWaveTable = 0;
            while ((curWaveTable < (m_baseWaveGroup->m_numWaveTables - 1) &&
                    (inc >= m_baseWaveGroup->m_WaveTables[curWaveTable]->m_topFreq))) {
                ++curWaveTable;
            }
        }
        currentVoice->m_baseWaveTable = m_baseWaveGroup->m_WaveTables[curWaveTable];
    } else {
        currentVoice->m_currentWaveTable = m_voices[currentMainVoice]->m_currentWaveTable;
        currentVoice->m_baseWaveTable = m_voices[currentMainVoice]->m_baseWaveTable;
    }
}

float WaveTableOscillator::getOutputRaw(int voice, float phaseOffset) {
    auto cVoice = m_voices[voice];
    if (cVoice->m_baseWaveTable != nullptr) {
        float phase = (float) cVoice->m_phasor + phaseOffset;
        auto sum = getOutputForPhaseAndWaveTable(cVoice->m_baseWaveTable, phase);
        auto finalSum = getOutputForPhaseAndWaveTable(cVoice->m_currentWaveTable, phase);
        return mixTables(sum, finalSum);
    }
    return 0;
}

float WaveTableOscillator::getOutputPWM(int voice) {
    auto offset = m_voices[voice]->m_phaseOfs;
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
    m_baseWaveGroup = WaveTableGenerator::getInstance().getGroup(WaveForms::SAW);
    m_currentWaveGroup = WaveTableGenerator::getInstance().getGroup(table);
    return m_currentWaveGroup == nullptr || m_baseWaveGroup == nullptr;
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
    for (auto &voice : m_voices) {
        voice->m_phasor = 0;
    }
}

WaveTableOscillator::~WaveTableOscillator ()
{
    for (auto &voice : m_voices) {
        delete voice;
    }
}
