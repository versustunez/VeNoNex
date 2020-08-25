#ifndef VENO_WAVETABLEGENERATOR_H
#define VENO_WAVETABLEGENERATOR_H

#include "JuceHeader.h"

struct WaveTableObject
{
    ~WaveTableObject() {
        m_waveTable.clear();
    }
    double m_topFreq;
    int m_waveTableLen;
    std::vector<float> m_waveTable = {};
};

struct WaveTableGroup
{
    static constexpr int numWaveTableSlots = 40;
    WaveTableObject* m_WaveTables[numWaveTableSlots] = {};
    int m_numWaveTables = 0;

    ~WaveTableGroup() {
        for (auto & m_WaveTable : m_WaveTables)
        {
            delete m_WaveTable;
        }
    }
};

enum WaveForms
{
    SAW = 0,
    SINE,
    SQUARE,
    TRIANGLE,
    DIRTY_SAW,
    DIRTY_SQUARE, //that stuff is to dirty xD,
    SYNTH_ONE,
    SYNTH_TWO,
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
    int addedWaveForms = 0;
    WaveTableGenerator () = default;
    ~WaveTableGenerator () = default;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (WaveTableGenerator)
};
#endif //VENO_WAVETABLEGENERATOR_H
