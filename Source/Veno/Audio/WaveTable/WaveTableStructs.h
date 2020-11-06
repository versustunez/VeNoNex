#pragma once

namespace VeNo
{
    struct WaveTableObject
    {
        double m_topFreq = 0.0;
        int m_waveTableLen = 0;
        std::vector<double> m_waveTable = {};
    };

    struct WaveTableGroup
    {
        static constexpr int numWaveTableSlots = 40;
        std::vector<WaveTableObject*> m_WaveTables{numWaveTableSlots};
        int m_numWaveTables = 0;

        ~WaveTableGroup ()
        {
            for (auto& m_WaveTable : m_WaveTables)
            {
                delete m_WaveTable;
            }
        }
    };

    enum WaveForms
    {
        SAW = 0,
        SINE,
        COSINE,
        SQUARE,
        TRIANGLE,
        DIRTY_SAW,
        DIRTY_SQUARE,
        SYNTH_ONE,
        SYNTH_TWO,
        VENOX,
        NOISE,
        SMOOTH_NOISE,
        SMOOTHER_NOISE,
    };
}