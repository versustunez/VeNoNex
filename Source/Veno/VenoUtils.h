//
// Created by Maurice on 31.10.2019.
//

#ifndef VENO_VENOUTILS_H
#define VENO_VENOUTILS_H

#include <cmath>

class VenoUtils {
public:
    static float DB_GAIN_CONVERSION_MULT;
    static int NOTES_PER_OCTAVE;
    static int CENTS_PER_NOTE;
    static int CENTS_PER_OCTAVE;

    static float poly_blep(float t, float phaseInc);

    static float lerp(float a, float b, float f);

    static float clamp(float value, float min, float max);

    static float centsToRatio(float cents);

    static float gainToDb(float gain);

    static float dbToGain(float decibels);

    static float interpolate(float from, float to, float t);

    static int nextPowerOfTwo(float value);
};

#endif //VENO_VENOUTILS_H
