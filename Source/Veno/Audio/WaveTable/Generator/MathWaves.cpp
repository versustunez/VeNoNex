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
        auto cosine = CosineWave();
        cosine.m_isRaw = true;
        cosine.m_index = WaveForms::COSINE;
        TableCreatorHelper::createTable(cosine);
    }
}