#include "Filter.h"

namespace VeNo
{

    Filter::Filter ()
    {
        m_filters.emplace_back ();
        m_filters.emplace_back ();
    }

    void Filter::update (double freq, double qFactor, double sRate, FilterType type, double gain)
    {
        if (m_freq != freq || m_qFactor != qFactor || m_sRate != sRate || m_type != type || gain != m_gain)
        {
            m_freq = freq;
            m_qFactor = qFactor;
            m_sRate = sRate;
            m_type = type;
            m_gain = gain;
            IIRCoefficients coefficients;
            switch (type)
            {
                case NO:
                    break;
                case LP:
                case LP2:
                    coefficients = juce::IIRCoefficients::makeLowPass (sRate, freq, qFactor);
                    break;
                case BP:
                    coefficients = juce::IIRCoefficients::makeBandPass (sRate, freq, qFactor);
                    break;
                case HP:
                    coefficients = juce::IIRCoefficients::makeHighPass (sRate, freq, qFactor);
                    break;
                case LS:
                    coefficients = juce::IIRCoefficients::makeLowShelf (sRate, freq, qFactor, gain);
                    break;
                case HS:
                    coefficients = juce::IIRCoefficients::makeHighShelf (sRate, freq, qFactor, gain);
                    break;
                case NOTCH:
                    coefficients = juce::IIRCoefficients::makeNotchFilter (sRate, freq, qFactor);
                    break;
                case PEAK:
                    coefficients = juce::IIRCoefficients::makePeakFilter (sRate, freq, qFactor, gain);
                    break;
            }
            if (type > FilterType::NO)
                setCoef (coefficients);
        }
    }

    void Filter::process (AudioBuffer<float>& buffer)
    {
        if (m_type == FilterType::NO)
            return;

        for (int i = 0; i < m_filters.size (); ++i)
        {
            m_filters[i].processSamples (buffer.getWritePointer (i), buffer.getNumSamples ());
        }
    }

    void Filter::setCoef (IIRCoefficients& coef)
    {
        for (auto& filter : m_filters)
        {
            filter.setCoefficients (coef);
        }
    }

    void Filter::processRaw (std::vector<double>& values)
    {
        if (m_type == FilterType::NO)
            return;
        values[1] = m_filters[0].processSingleSampleRaw (values[1]);
        values[2] = m_filters[1].processSingleSampleRaw (values[2]);
    }

    Filter::~Filter () = default;

}