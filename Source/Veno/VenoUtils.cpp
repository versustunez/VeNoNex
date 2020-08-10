//
// Created by versustune on 27.04.20.
//
#include "VenoUtils.h"

float VenoUtils::DB_GAIN_CONVERSION_MULT = 20.0;
int VenoUtils::NOTES_PER_OCTAVE = 12;
int VenoUtils::CENTS_PER_NOTE = 100;
int VenoUtils::CENTS_PER_OCTAVE = NOTES_PER_OCTAVE * CENTS_PER_NOTE;

float VenoUtils::poly_blep(float t, float phaseInc) {
    float DOUBLE_PI = 6.283185307179586476925286766559;
    double dt = phaseInc / DOUBLE_PI;
    if (t < dt) {
        t /= dt;
        return t + t - t * t - 1.0;
    } else if (t > 1.0 - dt) {
        t = (t - 1.0) / dt;
        return t * t + t + t + 1.0;
    } else return 0.0;
}

float VenoUtils::lerp(float a, float b, float f) {
    return (a + (b - a) * f);
}

float VenoUtils::clamp(float value, float min, float max) {
    return value > max ? max : value < min ? min : value;
}

float VenoUtils::centsToRatio(float cents) {
    return std::pow(2.0, cents / CENTS_PER_OCTAVE);
}

float VenoUtils::gainToDb(float gain) {
    return DB_GAIN_CONVERSION_MULT * std::log10(gain);
}

float VenoUtils::dbToGain(float decibels) {
    return pow(10.0, decibels / DB_GAIN_CONVERSION_MULT);
}

float VenoUtils::interpolate(float from, float to, float t) {
    return t * (to - from) + from;
}

int VenoUtils::nextPowerOfTwo(float value) {
    unsigned int v = value;
    v--;
    v |= v >> 1;
    v |= v >> 2;
    v |= v >> 4;
    v |= v >> 8;
    v |= v >> 16;
    v++;
    return v;
}