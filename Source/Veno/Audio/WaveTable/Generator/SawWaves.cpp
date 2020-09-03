#include "SawWaves.h"
#include "../TableCreatorHelper.h"

namespace VeNo
{
    void SawWave::generate ()
    {
        m_freqWaveRe[0] = m_freqWaveRe[m_len >> 1u] = 0.0;
        for (int i = 1; i < (m_len >> 1u); i++)
        {
            m_freqWaveRe[i] = 1.0 / i;
            m_freqWaveRe[m_len - i] = -m_freqWaveRe[i];
        }
    }

    void SawWave::startCreation ()
    {
        auto saw = SawWave();
        saw.m_index = WaveForms::SAW;
        TableCreatorHelper::createTable(saw);
    }

    void DirtySawWave::generate ()
    {
        int offset = static_cast<int>(m_len) / 64;
        std::srand (50);
        m_freqWaveRe[0] = m_freqWaveRe[m_len >> 1u] = 0.0;
        for (int i = 1; i < (m_len >> 1u); i++)
        {
            double value = 1.0 / i;
            if (i % offset == 0)
                value += TableCreatorHelper::getNextRand () * 0.003;

            m_freqWaveRe[i] = value;
            m_freqWaveRe[m_len - i] = -m_freqWaveRe[i];
        }
    }

    void DirtySawWave::startCreation ()
    {
        auto dSaw = DirtySawWave();
        dSaw.m_index = WaveForms::DIRTY_SAW;
        TableCreatorHelper::createTable(dSaw);
    }
}

