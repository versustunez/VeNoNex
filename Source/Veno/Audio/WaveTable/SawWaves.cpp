//
// Created by versustune on 08.06.20.
//

#include "WaveTableGenerator.h"
#include "../../Utils/Logger.h"
#include "TableHelper.h"

void generateSaw (WaveTableGroup* group)
{
    if (group == nullptr)
    {
        return;
    }
    int tableLen = findTableLen ();
    int idx;
    auto* freqWaveRe = new double[tableLen];
    auto* freqWaveIm = new double[tableLen];
    for (idx = 0; idx < tableLen; idx++)
    {
        freqWaveIm[idx] = 0.0;
    }
    freqWaveRe[0] = freqWaveRe[tableLen >> 1] = 0.0;
    for (idx = 1; idx < (tableLen >> 1); idx++)
    {
        freqWaveRe[idx] = 1.0 / idx;                    // sawtooth spectrum
        freqWaveRe[tableLen - idx] = -freqWaveRe[idx];  // mirror
    }
    fillTables (group, freqWaveRe, freqWaveIm, tableLen);
    VeNo::Logger::infoDebugMessage ("Generated clean Saw Wave");
}