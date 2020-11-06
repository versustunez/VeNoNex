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

    void createNoise (RawTable& table, int offset, int seed = 10000)
    {
        std::mt19937 mt (seed);
        std::uniform_real_distribution<double> dist (-1.0, 1.0);
        // some basic 1d simplex noise!
        double val = dist (mt);
        for (int i = 0; i < table.m_len; ++i)
        {
            if (i % offset == 0 && i != 0)
            {
                val = dist (mt);
            }
            table.m_freqWaveRe[i] = val;
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
        createNoise(*this, 64, 10000);
    }

    void SmootherNoise::startCreation ()
    {
        auto smootherNoise = SmootherNoise ();
        smootherNoise.m_isRaw = true;
        smootherNoise.m_index = WaveForms::SMOOTHER_NOISE;
        TableCreatorHelper::createTable (smootherNoise);
    }

    // sampleAndHold
    void SmootherNoise::generate ()
    {
        createNoise(*this, 256, 100500);
    }
}