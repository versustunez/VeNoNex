//
// Created by versustune on 08.06.20.
//

#ifndef VENO_WAVETABLEGENERATOR_H
#define VENO_WAVETABLEGENERATOR_H

#include "JuceHeader.h"

struct WaveTableObject
{
    double m_topFreq;
    int m_waveTableLen;
    float* m_waveTable;
};
struct WaveTableGroup
{
    static constexpr int numWaveTableSlots = 40;
    WaveTableObject* m_WaveTables[numWaveTableSlots] = {};
    int m_numWaveTables = 0;
};
enum WaveForms
{
    SAW = 0,
    SINE,
    SQUARE,
    TRIANGLE,
    wSaw,
    wSQUARE, //that stuff is to dirty xD,
    SYNTHONE,
    SYNTHTWO,
    VENOX
};
class WaveTableGenerator
{
private:
    static constexpr int numWaveTableSlots = 40;
    WaveTableGroup* m_waveTables[numWaveTableSlots] = {};
public:
    static WaveTableGenerator& getInstance ()
    {
        static WaveTableGenerator instance;
        return instance;
    }

    WaveTableGroup* getGroup (int id);
    void init ();
    void cleanTables ();
protected:
    bool m_isInit = false;
    WaveTableGenerator () = default;
    ~WaveTableGenerator () = default;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (WaveTableGenerator)
};
#endif //VENO_WAVETABLEGENERATOR_H
