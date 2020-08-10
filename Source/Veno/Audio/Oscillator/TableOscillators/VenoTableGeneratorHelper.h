//
// Created by versustune on 2020-02-28.
//

#include <cmath>
#include <cstdlib>
#include "VenoWaveTableGenerator.h"
#include "../../../VenoUtils.h"

#define M_PI        3.14159265358979323846
#define DOUBLE_PI   6.283185307179586476925286766559

/*
 in-place complex fft

 After Cooley, Lewis, and Welch; from Rabiner & Gold (1975)

 program adapted from FORTRAN
 by K. Steiglitz  (ken@princeton.edu)
 Computer Science Dept.
 Princeton University 08544
*/
void fft(int N, double *ar, double *ai) {
    int i, j, k, L;            /* indexes */
    int M, TEMP, LE, LE1, ip;  /* M = log N */
    int NV2, NM1;
    double t;               /* temp */
    double Ur, Ui, Wr, Wi, Tr, Ti;
    double Ur_old;

    // if ((N > 1) && !(N & (N - 1)))   // make sure we have a power of 2

    NV2 = N >> 1;
    NM1 = N - 1;
    TEMP = N; /* get M = log N */
    M = 0;
    while (TEMP >>= 1) ++M;

    /* shuffle */
    j = 1;
    for (i = 1; i <= NM1; i++) {
        if (i < j) {             /* swap a[i] and a[j] */
            t = ar[j - 1];
            ar[j - 1] = ar[i - 1];
            ar[i - 1] = t;
            t = ai[j - 1];
            ai[j - 1] = ai[i - 1];
            ai[i - 1] = t;
        }

        k = NV2;             /* bit-reversed counter */
        while (k < j) {
            j -= k;
            k /= 2;
        }

        j += k;
    }

    LE = 1.;
    for (L = 1; L <= M; L++) {            // stage L
        LE1 = LE;                         // (LE1 = LE/2)
        LE *= 2;                          // (LE = 2^L)
        Ur = 1.0;
        Ui = 0.;
        Wr = std::cos(M_PI / (float) LE1);
        Wi = -std::sin(M_PI / (float) LE1); // Cooley, Lewis, and Welch have "+" here
        for (j = 1; j <= LE1; j++) {
            for (i = j; i <= N; i += LE) { // butterfly
                ip = i + LE1;
                Tr = ar[ip - 1] * Ur - ai[ip - 1] * Ui;
                Ti = ar[ip - 1] * Ui + ai[ip - 1] * Ur;
                ar[ip - 1] = ar[i - 1] - Tr;
                ai[ip - 1] = ai[i - 1] - Ti;
                ar[i - 1] = ar[i - 1] + Tr;
                ai[i - 1] = ai[i - 1] + Ti;
            }
            Ur_old = Ur;
            Ur = Ur_old * Wr - Ui * Wi;
            Ui = Ur_old * Wi + Ui * Wr;
        }
    }
}

float makeWaveTable(WaveTableGroup *group, int len, double *ar, double *ai, double scale, double topFreq) {
    fft(len, ar, ai);

    if (scale == 0.0) {
        // calc normal
        double max = 0;
        for (int idx = 0; idx < len; idx++) {
            double temp = fabs(ai[idx]);
            if (max < temp)
                max = temp;
        }
        scale = 1.0 / max * .999;
    }

    // normalize
    auto *wave = new float[len];
    for (int idx = 0; idx < len; idx++)
        wave[idx] = ai[idx] * scale;

    if (group->numWaveTables < WaveTableGroup::numWaveTableSlots) {
        auto table = group->mWaveTables[group->numWaveTables] = new WaveTableObject();
        float *waveTable = group->mWaveTables[group->numWaveTables]->waveTable = new float[len + 1];
        table->waveTableLen = len;
        table->topFreq = topFreq;
        ++group->numWaveTables;

        // fill in wave
        for (long idx = 0; idx < len; idx++)
            waveTable[idx] = wave[idx];
        waveTable[len] = waveTable[0];  // duplicate for interpolation wraparound

        return 0;
    } else {
        scale = 0.0;
    }
    return (float) scale;
}

// utils stuff
int fillTables(WaveTableGroup *group, double *freqWaveRe, double *freqWaveIm, int numSamples) {
    int idx;

    freqWaveRe[0] = freqWaveIm[0] = 0.0;
    freqWaveRe[numSamples >> 1] = freqWaveIm[numSamples >> 1] = 0.0;

    int maxHarmonic = numSamples >> 1;
    const double minVal = 0.000001; // -120 dB
    while ((fabs(freqWaveRe[maxHarmonic]) + fabs(freqWaveIm[maxHarmonic]) < minVal) && maxHarmonic) --maxHarmonic;

    double topFreq = 2.0 / 3.0 / maxHarmonic;

    double *ar = new double[numSamples];
    double *ai = new double[numSamples];
    double scale = 0.0;
    int numTables = 0;
    while (maxHarmonic) {
        // fill the table in with the needed harmonics
        for (idx = 0; idx < numSamples; idx++)
            ar[idx] = ai[idx] = 0.0;
        for (idx = 1; idx <= maxHarmonic; idx++) {
            ar[idx] = freqWaveRe[idx];
            ai[idx] = freqWaveIm[idx];
            ar[numSamples - idx] = freqWaveRe[numSamples - idx];
            ai[numSamples - idx] = freqWaveIm[numSamples - idx];
        }

        // make the wavetable
        scale = makeWaveTable(group, numSamples, ar, ai, scale, topFreq);
        numTables++;

        // prepare for next table
        topFreq *= 2;
        maxHarmonic >>= 1;
    }
    return numTables;
}

float getNextRand() {
    return std::rand() / double(RAND_MAX);
}
