//
// Created by versustune on 08.06.20.
//

#include "SineWaves.h"
#include "../../Utils/Logger.h"
#include "TableHelper.h"
#include "../../Core/AudioConfig.h"

void SineWaves::generateSine(WaveTableGroup* group)
{
    if (group == nullptr)
    {
        return;
    }
    int tableLen = findTableLen();
    int idx;
    auto* freqWaveRe = new double[tableLen];
    auto* freqWaveIm = new double[tableLen];

    for (idx = 0; idx < tableLen; idx++)
    {
        freqWaveIm[idx] = 0.0;
    }
    float angleDelta = 6.28318530718 / (tableLen);
    float currentAngle = 0;
    for (idx = 0; idx < tableLen; idx++)
    {
        freqWaveRe[idx] = std::sin(currentAngle);
        currentAngle += angleDelta;
    }
    auto table = group->m_WaveTables[group->m_numWaveTables] = new WaveTableObject();
    auto& waveTable = group->m_WaveTables[group->m_numWaveTables]->m_waveTable;
    waveTable.resize(tableLen + 1);
    table->m_waveTableLen = tableLen;
    table->m_topFreq = AudioConfig::getInstance()->getSampleRate() / 2;
    ++group->m_numWaveTables;

    // fill in wave
    for (long x = 0; x < tableLen; x++)
        waveTable[x] = freqWaveRe[x];
    waveTable[tableLen] = waveTable[0];
    delete[] freqWaveRe;
    delete[] freqWaveIm;
    VeNo::Logger::infoDebugMessage("Generated clean Sine WaveTable");
}