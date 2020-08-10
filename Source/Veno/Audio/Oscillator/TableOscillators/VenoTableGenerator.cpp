//
// Created by versustune on 2020-02-28.
//

#include <cmath>
#include <cstdlib>
#include "VenoTableGeneratorHelper.h"
#include "VenoWaveTableGenerator.h"
#include "../../../VenoUtils.h"

#define M_PI        3.14159265358979323846
#define DOUBLE_PI   6.283185307179586476925286766559

void generateSaw(WaveTableGroup *group) {
    if (group == nullptr) {
        return;
    }
    int maxHarms = VenoWaveTableGenerator::getInstance().sampleRate / (3.0 * 20) + 0.5;
    int tableLen = VenoUtils::nextPowerOfTwo(maxHarms) * 2;
    int idx;
    auto *freqWaveRe = new double[tableLen];
    auto *freqWaveIm = new double[tableLen];

    for (idx = 0; idx < tableLen; idx++) {
        freqWaveIm[idx] = 0.0;
    }
    freqWaveRe[0] = freqWaveRe[tableLen >> 1] = 0.0;
    for (idx = 1; idx < (tableLen >> 1); idx++) {
        freqWaveRe[idx] = 1.0 / idx;                    // sawtooth spectrum
        freqWaveRe[tableLen - idx] = -freqWaveRe[idx];  // mirror
    }
    fillTables(group, freqWaveRe, freqWaveIm, tableLen);
}

void generateDirtySaw(WaveTableGroup *group) {
    if (group == nullptr) {
        return;
    }
    std::srand((unsigned) 404);
    int maxHarms = VenoWaveTableGenerator::getInstance().sampleRate / (3.0 * 20) + 0.5;
    int tableLen = VenoUtils::nextPowerOfTwo(maxHarms) * 2;
    int idx;
    auto *freqWaveRe = new double[tableLen];
    auto *freqWaveIm = new double[tableLen];

    for (idx = 0; idx < tableLen; idx++) {
        freqWaveIm[idx] = 0.0;
    }
    freqWaveRe[0] = freqWaveRe[tableLen >> 1] = 0.0;
    for (idx = 1; idx < (tableLen >> 1); idx++) {
        float value = 1.0 / idx;
        if (idx % 64 == 0) {
            value += ((std::rand() / double(RAND_MAX)) - 0.5) * 0.05;
        }
        freqWaveRe[idx] = value;                    // sawtooth spectrum
        freqWaveRe[tableLen - idx] = -freqWaveRe[idx];  // mirror
    }
    fillTables(group, freqWaveRe, freqWaveIm, tableLen);
}

void generateSquare(WaveTableGroup *group) {
    if (group == nullptr) {
        return;
    }
    int maxHarms = VenoWaveTableGenerator::getInstance().sampleRate / (3.0 * 20) + 0.5;
    int tableLen = VenoUtils::nextPowerOfTwo(maxHarms) * 2;
    int idx;
    auto *freqWaveRe = new double[tableLen];
    auto *freqWaveIm = new double[tableLen];

    for (idx = 0; idx < tableLen; idx++) {
        freqWaveIm[idx] = 0.0;
    }
    freqWaveRe[0] = freqWaveRe[tableLen >> 1] = 0.0;
    for (idx = 1; idx < (tableLen >> 1); idx++) {
        float temp = idx & 0x01 ? 1.0 / idx : 0.0;
        freqWaveRe[idx] = -temp;
        freqWaveRe[tableLen - idx] = temp;
    }
    fillTables(group, freqWaveRe, freqWaveIm, tableLen);
}

void generateSquareDirty(WaveTableGroup *group) {
    if (group == nullptr) {
        return;
    }
    std::srand((unsigned) 304);
    int maxHarms = VenoWaveTableGenerator::getInstance().sampleRate / (3.0 * 20) + 0.5;
    int tableLen = VenoUtils::nextPowerOfTwo(maxHarms) * 2;
    int idx;
    auto *freqWaveRe = new double[tableLen];
    auto *freqWaveIm = new double[tableLen];

    for (idx = 0; idx < tableLen; idx++) {
        freqWaveIm[idx] = 0.0;
    }
    freqWaveRe[0] = freqWaveRe[tableLen >> 1] = 0.0;
    for (idx = 1; idx < (tableLen >> 1); idx++) {
        float temp = idx & 0x01 ? 1.0 / idx : 0.0;
        if (idx % 64 == 0) {
            temp += ((std::rand() / double(RAND_MAX)) - 0.5) * 0.05;
        }
        freqWaveRe[idx] = -temp;
        freqWaveRe[tableLen - idx] = temp;
    }
    fillTables(group, freqWaveRe, freqWaveIm, tableLen);
}

void generateTriangle(WaveTableGroup *group) {
    if (group == nullptr) {
        return;
    }
    int maxHarms = VenoWaveTableGenerator::getInstance().sampleRate / (3.0 * 20) + 0.5;
    int tableLen = VenoUtils::nextPowerOfTwo(maxHarms) * 2;
    int idx;
    auto *freqWaveRe = new double[tableLen];
    auto *freqWaveIm = new double[tableLen];

    for (idx = 0; idx < tableLen; idx++) {
        freqWaveIm[idx] = 0.0;
    }
    freqWaveRe[0] = freqWaveRe[tableLen >> 1] = 0.0;
    float sign = 0.9;
    for (idx = 1; idx < (tableLen >> 1); idx++) {
        float temp = idx & 0x01 ? 1.0 / (idx * idx) * (sign = -sign) : 0.0;
        freqWaveRe[idx] = -temp;
        freqWaveRe[tableLen - idx] = temp;
    }
    fillTables(group, freqWaveRe, freqWaveIm, tableLen);
}

void generateSine(WaveTableGroup *group) {
    if (group == nullptr) {
        return;
    }
    int maxHarms = VenoWaveTableGenerator::getInstance().sampleRate / (3.0 * 20) + 0.5;
    int tableLen = VenoUtils::nextPowerOfTwo(maxHarms) * 2;
    int idx;
    auto *freqWaveRe = new double[tableLen];
    auto *freqWaveIm = new double[tableLen];

    for (idx = 0; idx < tableLen; idx++) {
        freqWaveIm[idx] = 0.0;
    }
    float angleDelta = 6.28318530718 / (tableLen);
    float currentAngle = 0;
    for (idx = 0; idx < tableLen; idx++) {
        freqWaveRe[idx] = std::sin(currentAngle);
        currentAngle += angleDelta;
    }
    auto table = group->mWaveTables[group->numWaveTables] = new WaveTableObject();
    float *waveTable = group->mWaveTables[group->numWaveTables]->waveTable = new float[tableLen];
    table->waveTableLen = tableLen;
    table->topFreq = VenoWaveTableGenerator::getInstance().sampleRate / 2;
    ++group->numWaveTables;

    // fill in wave
    for (long x = 0; x < tableLen; x++)
        waveTable[x] = freqWaveRe[x];
    waveTable[tableLen] = waveTable[0];
}

void generateSynth1(WaveTableGroup *group) {
    if (group == nullptr) {
        return;
    }
    std::srand((unsigned) 303);
    int maxHarms = VenoWaveTableGenerator::getInstance().sampleRate / (3.0 * 20) + 0.5;
    int tableLen = VenoUtils::nextPowerOfTwo(maxHarms) * 2;
    int idx;
    auto *freqWaveRe = new double[tableLen];
    auto *freqWaveIm = new double[tableLen];

    for (idx = 0; idx < tableLen; idx++) {
        freqWaveIm[idx] = 0.0;
    }
    freqWaveRe[0] = freqWaveRe[tableLen >> 1] = 0.0;
    for (idx = 1; idx < (tableLen >> 1); idx++) {
        freqWaveRe[idx] = getNextRand() / idx;
        freqWaveRe[tableLen - idx] = -freqWaveRe[idx];  // mirror
    }
    fillTables(group, freqWaveRe, freqWaveIm, tableLen);
}

void generateSynth2(WaveTableGroup *group) {
    if (group == nullptr) {
        return;
    }
    std::srand((unsigned) 306);
    int maxHarms = VenoWaveTableGenerator::getInstance().sampleRate / (3.0 * 20) + 0.5;
    int tableLen = VenoUtils::nextPowerOfTwo(maxHarms) * 2;
    int idx;
    auto *freqWaveRe = new double[tableLen];
    auto *freqWaveIm = new double[tableLen];

    for (idx = 0; idx < tableLen; idx++) {
        freqWaveIm[idx] = 0.0;
    }
    freqWaveRe[0] = freqWaveRe[tableLen >> 1] = 0.0;
    for (idx = 1; idx < (tableLen >> 1); idx++) {
        freqWaveRe[idx] = getNextRand() / idx;
        freqWaveRe[tableLen - idx] = -freqWaveRe[idx];  // mirror
    }
    fillTables(group, freqWaveRe, freqWaveIm, tableLen);
}

void generateVenoX(WaveTableGroup *group) {
    if (group == nullptr) {
        return;
    }
    std::srand((unsigned) 304190);
    int maxHarms = VenoWaveTableGenerator::getInstance().sampleRate / (3.0 * 20) + 0.5;
    int tableLen = VenoUtils::nextPowerOfTwo(maxHarms) * 2;
    int idx;
    auto *freqWaveRe = new double[tableLen];
    auto *freqWaveIm = new double[tableLen];

    for (idx = 0; idx < tableLen; idx++) {
        freqWaveIm[idx] = 0.0;
    }
    freqWaveRe[0] = freqWaveRe[tableLen >> 1] = 0.0;
    for (idx = 1; idx < (tableLen >> 1); idx++) {
        freqWaveRe[idx] = (getNextRand() * getNextRand()) / idx;
        freqWaveRe[tableLen - idx] = -(getNextRand() / idx);  // mirror
    }
    fillTables(group, freqWaveRe, freqWaveIm, tableLen);
}
