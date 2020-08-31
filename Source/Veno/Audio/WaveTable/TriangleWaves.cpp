#include "TriangleWaves.h"
#include "../../Utils/Logger.h"
#include "TableHelper.h"

void TriangleWaves::generateTriangle (WaveTableGroup* group)
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
    double sign = 0.9;
    for (idx = 1; idx < (tableLen >> 1); idx++)
    {
        double temp = idx & 0x01 ? 1.0 / (idx * idx) * (sign = -sign) : 0.0;
        freqWaveRe[idx] = -temp;
        freqWaveRe[tableLen - idx] = temp;
    }
    fillTables (group, freqWaveRe, freqWaveIm, tableLen);
    VeNo::Logger::infoDebugMessage ("Generated clean Triangle WaveTable");
}
