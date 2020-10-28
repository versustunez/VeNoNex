#include "WaveTableGenerator.h"
#include "../../Core/AudioConfig.h"
#include "WavesInlcuder.h"

namespace VeNo
{
    void WaveTableGenerator::init ()
    {
        if (m_isInit)
        {
            return;
        }
        m_waveTables.reserve (WaveForms::SMOOTH_NOISE + 1);
        SawWave::startCreation ();
        DirtySawWave::startCreation ();
        SineWave::startCreation ();
        CosineWave::startCreation ();
        SquareWave::startCreation ();
        DirtySquareWave::startCreation ();
        TriangleWave::startCreation ();
        SynthTwo::startCreation ();
        SynthOne::startCreation ();
        VeNoX::startCreation ();
        Noise::startCreation();
        SmoothNoise::startCreation();

        addedWaveForms = m_waveTables.capacity ();
        m_isInit = true;
    }

    WaveTableGroup* WaveTableGenerator::getGroup (int id)
    {
        if (!m_isInit)
        {
            init ();
        }
        return m_waveTables[id];
    }

    void WaveTableGenerator::cleanTables ()
    {
        if (m_isInit)
        {
            for (int i = 0; i < addedWaveForms; i++)
            {
                auto& table = m_waveTables[i];
                if (table != nullptr)
                {
                    for (int j = 0; j < table->m_numWaveTables; j++)
                    {
                        delete table->m_WaveTables[j];
                        table->m_WaveTables[j] = nullptr;
                    }
                    delete table;
                    table = nullptr;
                }
            }
        }
        addedWaveForms = 0;
        m_isInit = false;
    }

    void WaveTableGenerator::setGroup (WaveForms index, WaveTableGroup* group)
    {
        m_waveTables[index] = group;
    }
}