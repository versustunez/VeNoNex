//
// Created by versustune on 12.06.20.
//

#ifndef VENO_FFT_H
#define VENO_FFT_H

#include "JuceHeader.h"

class FFT
{
private:
public:
    FFT () = default;
    ~FFT () = default;
    void pushNextSampleIntoFifo (float sample) noexcept;
    enum
    {
        fftOrder = 11,            // [1]
        fftSize = 1 << fftOrder, // [2]
        scopeSize = 512            // [3]
    };
    void drawNextFrameOfSpectrum ();
    bool nextFFTBlockReady = false;
    float scopeData[scopeSize]{};
    float fftData[2 * fftSize]{};
protected:
    dsp::FFT fft{fftOrder};
    dsp::WindowingFunction<float> window{fftSize, dsp::WindowingFunction<float>::hann};
    float fifo[fftSize]{};
    int fifoIndex = 0;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FFT)
};
#endif //VENO_FFT_H
