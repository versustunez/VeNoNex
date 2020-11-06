#pragma once

#include "JuceHeader.h"
#include <vector>

namespace VeNo
{
    enum FilterType
    {
        NO = 0,
        LP = 1,
        LP2 = 2, // FIRST ORDER LP! NO JUCE :P
        BP = 3,
        HP = 4,
        LS = 5,
        HS = 6,
        NOTCH = 7,
        PEAK = 8
    };

    class Filter
    {
    public:
        Filter ();

        ~Filter ();

        void update (double freq, double qFactor, double sRate, FilterType type, double gain);

        void process (AudioBuffer<float>& buffer);

        void processRaw (std::vector<double>& values);

        double m_freq = 1;

        double m_qFactor = 1.0;
        double m_sRate = 44100;
        double m_gain = 1.0;
        int m_type = FilterType::NO;
    protected:
        void setCoef (IIRCoefficients& coef);

        std::vector<juce::IIRFilter> m_filters;
    };
}