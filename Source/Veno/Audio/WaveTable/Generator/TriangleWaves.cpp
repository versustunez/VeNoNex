#include "TriangleWaves.h"
#include "../TableCreatorHelper.h"

namespace VeNo
{

    void TriangleWave::generate ()
    {
        double sign = 0.9;
        for (unsigned int i = 1; i < (m_len >> 1u); i++)
        {
            double temp = (i & 0x01u) ? 1.0 / (i * i) * (sign = -sign) : 0.0;
            m_freqWaveRe[i] = -temp;
            m_freqWaveRe[m_len - i] = temp;
        }
    }

    void TriangleWave::startCreation ()
    {
        auto tri = TriangleWave ();
        tri.m_index = WaveForms::TRIANGLE;
        TableCreatorHelper::createTable (tri);
    }
}