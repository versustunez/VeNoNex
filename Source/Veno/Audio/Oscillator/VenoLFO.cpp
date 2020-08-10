//
// Created by Maurice on 18.02.2020.
//

#include "VenoLFO.h"

void VenoLFO::update() {
    //same shit the updatePhase
    tableHelper.updatePhase(0);
}

float VenoLFO::getAmount(float amountStrength) {
    if (rate == 0) {
        return 0;
    }
    return tableHelper.getOutput(0) * (amount * amountStrength);
}

void VenoLFO::setRate(float rate) {
    if (VenoLFO::rate != rate) {
        VenoLFO::rate = rate;
        tableHelper.setFreq(rate, 0, 0, 0, 0);
    }
}

void VenoLFO::setAmount(float amount) {
    VenoLFO::amount = amount;
}

VenoLFO::VenoLFO() {
    setRate(1);
    tableHelper.setWaveTable(WaveForms::SAW);
    tableHelper.waveTableMix = 1;
}

VenoLFO::~VenoLFO() {

}

float VenoLFO::getRaw() {
    if (rate == 0) {
        return 0;
    }
    return tableHelper.getOutput(0);
}
