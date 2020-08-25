#include "WaveTableGenerator.h"
#include "../../Core/AudioConfig.h"
#include "WavesInlcuder.h"

void WaveTableGenerator::init()
{
    if (m_isInit)
    {
        return;
    }
    m_waveTables[WaveForms::SAW] = new WaveTableGroup();
    m_waveTables[WaveForms::SINE] = new WaveTableGroup();
    m_waveTables[WaveForms::SQUARE] = new WaveTableGroup();
    m_waveTables[WaveForms::TRIANGLE] = new WaveTableGroup();
    m_waveTables[WaveForms::DIRTY_SAW] = new WaveTableGroup();
    m_waveTables[WaveForms::DIRTY_SQUARE] = new WaveTableGroup();
    m_waveTables[WaveForms::SYNTH_ONE] = new WaveTableGroup();
    m_waveTables[WaveForms::SYNTH_TWO] = new WaveTableGroup();
    m_waveTables[WaveForms::VENOX] = new WaveTableGroup();
    SawWaves::generateSaw(m_waveTables[WaveForms::SAW]);
    SawWaves::generateDirtySaw(m_waveTables[WaveForms::DIRTY_SAW]);
    SineWaves::generateSine(m_waveTables[WaveForms::SINE]);
    SquareWaves::generateSquare(m_waveTables[WaveForms::SQUARE]);
    SquareWaves::generateDirtySquare(m_waveTables[WaveForms::DIRTY_SQUARE]);
    TriangleWaves::generateTriangle(m_waveTables[WaveForms::TRIANGLE]);
    addedWaveForms = WaveForms::VENOX + 1;
    m_isInit = true;
}

WaveTableGroup* WaveTableGenerator::getGroup(int id)
{
    if (!m_isInit)
    {
        init();
    }
    if (id < 40)
    {
        return m_waveTables[id];
    }
    return nullptr;
}

void WaveTableGenerator::cleanTables()
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
    m_isInit = false;
}
