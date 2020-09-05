#pragma once

#include <cmath>

namespace VeNo
{
    struct PeakReducer
    {
        int samplesToFin = 15;
        int sampleSincePeak = 0;
        double peakReduceAmount = 0;
        double threshold = 1.0;

        double limit (double sample)
        {
            if (sampleSincePeak++ < samplesToFin && peakReduceAmount != 0)
            {
                sample = detectPeak (sample * peakReduceAmount);
                peakReduceAmount *= 0.5;
            }
            else
            {
                peakReduceAmount = 0;
                sample = detectPeak (sample);
            }
            return sample;
        }

        double detectPeak (double sample)
        {
            bool peaked = false;
            if (sample > threshold || sample < -threshold)
            {
                peakReduceAmount = (threshold - 0.005) / std::fabs (sample);
                peaked = true;
            }

            if (peaked)
            {
                sample *= peakReduceAmount;
                sampleSincePeak = 0;
            }

            return sample;
        }
    };
}