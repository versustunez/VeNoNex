#ifndef VENO_FFT_H
#define VENO_FFT_H

#include "JuceHeader.h"

class FFT
{
private:
public:
    FFT () = default;
    ~FFT () = default;
    enum
    {
        fftOrder = 11,
        fftSize = 2048,
        scopeSize = 2048
    };
    void drawNextFrameOfSpectrum (const std::vector<float>& data);
    float scopeData[scopeSize]{};
    float fftData[2*fftSize]{};
protected:
    dsp::FFT fft{fftOrder};
    dsp::WindowingFunction<float> window{fftSize, dsp::WindowingFunction<float>::hann, true, false};
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FFT)
};
#endif //VENO_FFT_H
