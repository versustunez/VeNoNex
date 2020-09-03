#include "SquareWaves.h"
#include "../TableCreatorHelper.h"

namespace VeNo {
    void SquareWave::generate ()
    {
        m_freqWaveRe[0] = m_freqWaveRe[m_len >> 1u] = 0.0;
        for (unsigned int i = 1; i < (m_len >> 1u); i++)
        {
            double temp = (i & 0x01u) ? 1.0 / i : 0.0;
            m_freqWaveRe[i] = -temp;
            m_freqWaveRe[m_len - i] = temp;
        }
    }

    void SquareWave::startCreation ()
    {
        auto square = SquareWave();
        square.m_index = WaveForms::SQUARE;
        TableCreatorHelper::createTable(square);
    }

    void DirtySquareWave::generate ()
    {
        int offset = static_cast<int>(m_len) / 64;
        m_freqWaveRe[0] = m_freqWaveRe[m_len >> 1u] = 0.0;
        for (unsigned int i = 1; i < (m_len >> 1u); i++)
        {
            double temp = (i & 0x01u) ? 1.0 / i : 0.0;
            if (i % offset == 0)
                temp += TableCreatorHelper::getNextRand () * 0.0005;
            m_freqWaveRe[i] = -temp;
            m_freqWaveRe[m_len - i] = temp;
        }
    }

    void DirtySquareWave::startCreation ()
    {
        auto dSquare = DirtySquareWave();
        dSquare.m_index = WaveForms::DIRTY_SQUARE;
        TableCreatorHelper::createTable(dSquare);
    }
}

