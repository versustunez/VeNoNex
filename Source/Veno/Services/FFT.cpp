#include "FFT.h"
#include "../Utils.h"

using VeNo::Utils;

void FFT::drawNextFrameOfSpectrum (const std::vector<double>& data)
{
    for (int i = 0; i < data.size (); ++i)
    {
        if (i > fftSize)
        {
            break;
        }
        fftData[i] = data[i];
    }
    window.multiplyWithWindowingTable (fftData, fftSize);
    fft.performFrequencyOnlyForwardTransform (fftData);

    auto mindB = -100.0f;
    auto maxdB = 0.0f;
    for (int i = 0; i < scopeSize; ++i)
    {
        auto skewedProportionX = 1.0f - std::exp (std::log (1.0f - (double) i / (double) scopeSize) * 0.2f);
        int fftDataIndex = (int) Utils::clamp ((skewedProportionX * (double) fftSize * 0.5f), 0, fftSize / 2);
        auto gain = (float) Utils::clamp (
                Decibels::gainToDecibels (fftData[fftDataIndex]) - juce::Decibels::gainToDecibels ((float) fftSize),
                mindB, maxdB);
        scopeData[i] = juce::jmap (gain, mindB, maxdB, 1.0f, 0.1f);
    }
}