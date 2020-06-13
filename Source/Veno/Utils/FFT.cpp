//
// Created by versustune on 12.06.20.
//

#include "FFT.h"

void FFT::pushNextSampleIntoFifo (float sample) noexcept
{
    {
        if (fifoIndex == fftSize)    // [11]
        {
            if (!nextFFTBlockReady) // [12]
            {
                zeromem (fftData, sizeof (fftData));
                memcpy (fftData, fifo, sizeof (fifo));
                nextFFTBlockReady = true;
            }
            fifoIndex = 0;
        }
        fifo[fifoIndex++] = sample;  // [12]
    }
}

void FFT::drawNextFrameOfSpectrum ()
{
    window.multiplyWithWindowingTable (fftData, fftSize);      // [1]
    fft.performFrequencyOnlyForwardTransform (fftData); // [2]

    auto mindB = -80.0f;
    auto maxdB = 0.0f;
    for (int i = 0; i < scopeSize; ++i)
    {
        auto level = jmap (Decibels::gainToDecibels (fftData[i], mindB), mindB, maxdB, -1.0f, 1.0f);
        scopeData[i] = level;
    }
}
