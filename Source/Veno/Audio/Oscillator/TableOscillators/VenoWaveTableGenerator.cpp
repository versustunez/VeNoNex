//
// Created by versustune on 2020-02-28.
//

#include <iostream>
#include "VenoWaveTableGenerator.h"
#include "VenoTableGenerator.cpp"

WaveTableGroup *VenoWaveTableGenerator::getGroup(int id) {
    if (!isInit) {
        init();
    }
    if (id <= 40) {
        return waveTables[id];
    }
    return nullptr;
}

void VenoWaveTableGenerator::init() {
    if (isInit) {
        return;
    }
    waveTables[WaveForms::SAW] = new WaveTableGroup();
    waveTables[WaveForms::SINE] = new WaveTableGroup();
    waveTables[WaveForms::SQUARE] = new WaveTableGroup();
    waveTables[WaveForms::TRIANGLE] = new WaveTableGroup();
    waveTables[WaveForms::wSaw] = new WaveTableGroup();
    waveTables[WaveForms::wSQUARE] = new WaveTableGroup();
    waveTables[WaveForms::SYNTHONE] = new WaveTableGroup();
    waveTables[WaveForms::SYNTHTWO] = new WaveTableGroup();
    waveTables[WaveForms::VENOX] = new WaveTableGroup();

    generateSaw(waveTables[WaveForms::SAW]);
    generateSine(waveTables[WaveForms::SINE]);
    generateSquare(waveTables[WaveForms::SQUARE]);
    generateTriangle(waveTables[WaveForms::TRIANGLE]);
    generateDirtySaw(waveTables[WaveForms::wSaw]);
    generateSquareDirty(waveTables[WaveForms::wSQUARE]);
    generateSynth1(waveTables[WaveForms::SYNTHONE]);
    generateSynth2(waveTables[WaveForms::SYNTHTWO]);
    generateVenoX(waveTables[WaveForms::VENOX]);
    isInit = true;
}
