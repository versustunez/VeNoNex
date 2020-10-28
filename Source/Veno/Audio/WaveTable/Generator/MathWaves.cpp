#include <random>
#include "MathWaves.h"
#include "../TableCreatorHelper.h"

namespace VeNo {

    void SineWave::generate ()
    {
        double angleDelta = 6.28318530718 / (m_len);
        double currentAngle = 0;
        for (int i = 0; i < m_len; i++)
        {
            m_freqWaveRe[i] = std::sin (currentAngle);
            currentAngle += angleDelta;
        }
    }

    void SineWave::startCreation ()
    {
        auto sine = SineWave();
        sine.m_isRaw = true;
        sine.m_index = WaveForms::SINE;
        TableCreatorHelper::createTable(sine);
    }

    void CosineWave::generate ()
    {
        double angleDelta = 6.28318530718 / (m_len);
        double currentAngle = 0;
        for (int i = 0; i < m_len; i++)
        {
            m_freqWaveRe[i] = std::cos(currentAngle);
            currentAngle += angleDelta;
        }
    }

    void CosineWave::startCreation ()
    {
        auto cosine = CosineWave ();
        cosine.m_isRaw = true;
        cosine.m_index = WaveForms::COSINE;
        TableCreatorHelper::createTable (cosine);
    }

    void Noise::startCreation ()
    {
        auto noise = Noise ();
        noise.m_isRaw = true;
        noise.m_index = WaveForms::NOISE;
        TableCreatorHelper::createTable (noise);
    }

    // hard noising :D
    void Noise::generate ()
    {
        std::mt19937 mt (1000);
        std::uniform_real_distribution<double> dist (-1.0, 1.0);
        for (int i = 0; i < m_len; i++)
        {
            m_freqWaveRe[i] = dist (mt);
        }
    }

    void SmoothNoise::startCreation ()
    {
        auto noise = SmoothNoise ();
        noise.m_isRaw = true;
        noise.m_index = WaveForms::SMOOTH_NOISE;
        TableCreatorHelper::createTable (noise);
    }

    // sampleAndHold
    void SmoothNoise::generate ()
    {
        std::mt19937 mt (10000);
        std::uniform_real_distribution<double> dist (-1.0, 1.0);
        // some basic 1d simplex noise!
        int offset = m_len / 64;
        double val = dist (mt);
        for (int i = 0; i < m_len; ++i)
        {
            if (i % offset == 0)
            {
                val = dist (mt);
            }
            m_freqWaveRe[i] = val;
        }

    }
}