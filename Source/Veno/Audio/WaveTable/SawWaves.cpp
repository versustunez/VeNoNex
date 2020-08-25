#include "SawWaves.h"
#include "../../Utils/Logger.h"
#include "TableHelper.h"

void SawWaves::generateSaw (WaveTableGroup* group)
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
    VeNo::Logger::infoDebugMessage ("Generated clean Saw WaveTable");
}

void SawWaves::generateDirtySaw (WaveTableGroup* group)
{
    if (group == nullptr)
    {
        return;
    }
    std::srand ((unsigned) 404);
    int tableLen = findTableLen ();
    int idx;
    auto* freqWaveRe = new double[tableLen];
    auto* freqWaveIm = new double[tableLen];

    for (idx = 0; idx < tableLen; idx++)
    {
        freqWaveIm[idx] = 0.0;
    }
    freqWaveRe[0] = freqWaveRe[tableLen >> 1] = 0.0;
    int offset = tableLen / 64;
    for (idx = 1; idx < (tableLen >> 1); idx++)
    {
        float value = 1.0 / idx;
        if (idx % offset == 0)
        {
            value += ((std::rand () / double (RAND_MAX)) - 0.5) * 0.005;
        }
        freqWaveRe[idx] = value;                    // sawtooth spectrum
        freqWaveRe[tableLen - idx] = -freqWaveRe[idx];  // mirror
    }
    fillTables (group, freqWaveRe, freqWaveIm, tableLen);
    VeNo::Logger::infoDebugMessage ("Generated dirty Saw WaveTable");
}
