#ifndef VENO_DETUNELOOKUP_H
#define VENO_DETUNELOOKUP_H

#include "../../../../VenoUtils.h"
#include <iostream>
#include <vector>

namespace {
    const float MIN_LOOKUP_CENTS = -100.0;
    const float MAX_LOOKUP_CENTS = 100.0;
    const float CENTS_RANGE = MAX_LOOKUP_CENTS - MIN_LOOKUP_CENTS;
    const int DETUNE_LOOKUP_RESOLUTION = 2046;
}
class DetuneLookup {
public:
    bool alternate;

    float getCalculatedDetune(int voice) {
        float freq = lastFreq * lookupTable[voice];
        return freq;
    }

    void setNewLookup(float freq, int voices, float detune, float detuneDensity, int midiNote) {
        if (lookupTable.size() == 0
            || lastMidiNote != midiNote
            || lastDetune != detune
            || voices != lastVoices) {
            // calculate Detune :)
            auto real = voices + 1;
            lookupTable.resize(real);
            auto half = voices / 2;
            auto halfReal = real / 2;
            auto centPlus = (getRealDetune(detune) * preCalcedMidiNotes[lastMidiNote]) / real;
            auto cents = 0;
            int venoCount = 1;
            for (int i = 0; i < real; ++i) {
                if (i == half) {
                    venoCount = 1;
                    lookupTable[i] = 1;
                    continue;
                }
                if (detune == 0) {
                    lookupTable[i] = 1;
                    continue;
                }
                auto pos = venoCount / halfReal;
                cents += centPlus + (centPlus * (pos * pos * pos));
                if(i % 2 == 0) {
                    lookupTable[i] = 1 - (centsToRatio(cents) - 1);
                } else {
                    lookupTable[i] = (centsToRatio(cents));
                }
                venoCount++;
            }
            lastDetune = detune;
            lastVoices = voices;
        }
        lastMidiNote = midiNote;
        lastFreq = freq;
    }

protected:
    float getRealDetune(float detune) {
        if (detune != lastDetune) {
            float d = detune / 600;
            lastRealDetune = (d * d * d * d) * 900;
        }
        return lastRealDetune;
    }

    float centsToRatio(float cents) {
        return std::pow(2.0, cents / 1200);
    }

private:
    int lastMidiNote = 0;
    float lastRealDetune = 0;
    float lastDetune = 0;
    float lastFreq = 0;
    int lastVoices = 0;
    //helper.py has a value to do that!
    std::vector<float> lookupTable = {};

    float preCalcedMidiNotes[128] = {0, 0, 0, 0, 0, 0, 0, 0, 0.05511811023622047, 0.05511811023622047,
                                     0.05511811023622047, 0.05511811023622047, 0.05511811023622047, 0.05511811023622047,
                                     0.05511811023622047, 0.05511811023622047, 0.11811023622047244, 0.11811023622047244,
                                     0.11811023622047244, 0.11811023622047244, 0.11811023622047244, 0.11811023622047244,
                                     0.11811023622047244, 0.11811023622047244, 0.18110236220472442, 0.18110236220472442,
                                     0.18110236220472442, 0.18110236220472442, 0.18110236220472442, 0.18110236220472442,
                                     0.18110236220472442, 0.18110236220472442, 0.2440944881889764, 0.2440944881889764,
                                     0.2440944881889764, 0.2440944881889764, 0.2440944881889764, 0.2440944881889764,
                                     0.2440944881889764, 0.2440944881889764, 0.30708661417322836, 0.30708661417322836,
                                     0.30708661417322836, 0.30708661417322836, 0.30708661417322836, 0.30708661417322836,
                                     0.30708661417322836, 0.30708661417322836, 0.3700787401574803, 0.3700787401574803,
                                     0.3700787401574803, 0.3700787401574803, 0.3700787401574803, 0.3700787401574803,
                                     0.3700787401574803, 0.3700787401574803, 0.4330708661417323, 0.4330708661417323,
                                     0.4330708661417323, 0.4330708661417323, 0.4330708661417323, 0.4330708661417323,
                                     0.4330708661417323, 0.4330708661417323, 0.49606299212598426, 0.49606299212598426,
                                     0.49606299212598426, 0.49606299212598426, 0.49606299212598426, 0.49606299212598426,
                                     0.49606299212598426, 0.49606299212598426, 0.5590551181102362, 0.5590551181102362,
                                     0.5590551181102362, 0.5590551181102362, 0.5590551181102362, 0.5590551181102362,
                                     0.5590551181102362, 0.5590551181102362, 0.6220472440944882, 0.6220472440944882,
                                     0.6220472440944882, 0.6220472440944882, 0.6220472440944882, 0.6220472440944882,
                                     0.6220472440944882, 0.6220472440944882, 0.6850393700787402, 0.6850393700787402,
                                     0.6850393700787402, 0.6850393700787402, 0.6850393700787402, 0.6850393700787402,
                                     0.6850393700787402, 0.6850393700787402, 0.7480314960629921, 0.7480314960629921,
                                     0.7480314960629921, 0.7480314960629921, 0.7480314960629921, 0.7480314960629921,
                                     0.7480314960629921, 0.7480314960629921, 0.8110236220472441, 0.8110236220472441,
                                     0.8110236220472441, 0.8110236220472441, 0.8110236220472441, 0.8110236220472441,
                                     0.8110236220472441, 0.8110236220472441, 0.8740157480314961, 0.8740157480314961,
                                     0.8740157480314961, 0.8740157480314961, 0.8740157480314961, 0.8740157480314961,
                                     0.8740157480314961, 0.8740157480314961, 0.937007874015748, 0.937007874015748,
                                     0.937007874015748, 0.937007874015748, 0.937007874015748, 0.937007874015748,
                                     0.937007874015748, 1};
};

#endif //VENO_DETUNELOOKUP_H
