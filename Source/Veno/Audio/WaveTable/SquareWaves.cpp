#include "SquareWaves.h"
#include "../../Utils/Logger.h"
#include "TableHelper.h"

void SquareWaves::generateSquare (WaveTableGroup* group)
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
        float temp = idx & 0x01 ? 1.0 / idx : 0.0;
        freqWaveRe[idx] = -temp;
        freqWaveRe[tableLen - idx] = temp;
    }
    fillTables (group, freqWaveRe, freqWaveIm, tableLen);
    VeNo::Logger::infoDebugMessage ("Generated clean Square WaveTable");
}

void SquareWaves::generateDirtySquare (WaveTableGroup* group)
{
    if (group == nullptr)
    {
        return;
    }
    std::srand ((unsigned) 304);
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
        float temp = idx & 0x01 ? 1.0 / idx : 0.0;
        if (idx % 64 == 0)
        {
            temp += ((std::rand () / double (RAND_MAX)) - 0.5) * 0.005;
        }
        freqWaveRe[idx] = -temp;
        freqWaveRe[tableLen - idx] = temp;
    }
    fillTables (group, freqWaveRe, freqWaveIm, tableLen);
    VeNo::Logger::infoDebugMessage ("Generated dirty Square WaveTable");
}
