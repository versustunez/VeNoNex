//
// Created by versustune on 08.06.20.
//

#include "WaveTableGenerator.h"
#include "../../Core/AudioConfig.h"
#include "WavesInlcuder.h"

void WaveTableGenerator::init() {
    //if the sampleRate changed... the WaveTables are not harmonic Save anymore and are needed to rebuild... pls stay save later!
    if (AudioConfig::getInstance()->isNeedToReInit()) {
        cleanTables();
        AudioConfig::getInstance()->setNeedToReInit(false);
    }
    if (m_isInit) {
        return;
    }
    m_waveTables[WaveForms::SAW] = new WaveTableGroup();
    m_waveTables[WaveForms::SINE] = new WaveTableGroup();
    m_waveTables[WaveForms::SQUARE] = new WaveTableGroup();
    m_waveTables[WaveForms::TRIANGLE] = new WaveTableGroup();
    m_waveTables[WaveForms::wSaw] = new WaveTableGroup();
    m_waveTables[WaveForms::wSQUARE] = new WaveTableGroup();
    m_waveTables[WaveForms::SYNTHONE] = new WaveTableGroup();
    m_waveTables[WaveForms::SYNTHTWO] = new WaveTableGroup();
    m_waveTables[WaveForms::VENOX] = new WaveTableGroup();

    generateSaw(m_waveTables[WaveForms::SAW]);
    m_isInit = true;
}

WaveTableGroup *WaveTableGenerator::getGroup(int id) {
    if (!m_isInit) {
        init();
    }
    if (id < 40) {
        return m_waveTables[id];
    }
    return nullptr;
}

void WaveTableGenerator::cleanTables() {
    for (auto & m_waveTable : m_waveTables) {
        delete m_waveTable;
    }
    m_isInit = false;
}
