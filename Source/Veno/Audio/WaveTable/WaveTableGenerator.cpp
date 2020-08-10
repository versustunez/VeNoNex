//
// Created by versustune on 08.06.20.
//

#include "WaveTableGenerator.h"
#include "../../Core/AudioConfig.h"
#include "WavesInlcuder.h"

void WaveTableGenerator::init ()
{
    //if the sampleRate changed... the WaveTables are not harmonic Save anymore and are needed to rebuild... pls stay save later!
    if (AudioConfig::getInstance()->isNeedToReInit())
    {
        cleanTables();
        AudioConfig::getInstance()->setNeedToReInit(false);
    }
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
    m_isInit = true;
}

WaveTableGroup* WaveTableGenerator::getGroup (int id)
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

void WaveTableGenerator::cleanTables ()
{
    for (auto& m_waveTable : m_waveTables)
    {
        for (auto & m_WaveTable : m_waveTable->m_WaveTables)
        {
            if (m_waveTable != nullptr && m_WaveTable != nullptr) {
                delete[] m_WaveTable->m_waveTable;
                delete m_WaveTable;
            }
        }
        delete m_waveTable;
    }
    m_isInit = false;
}
