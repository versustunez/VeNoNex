#include "VeNoSpecials.h"
#include "../TableCreatorHelper.h"
#include "../../../Utils.h"

namespace VeNo
{

    void SynthOne::generate ()
    {
        std::srand ((unsigned) 303);
        int offset = static_cast<int>(m_len) / 128;
        m_freqWaveRe[0] = m_freqWaveRe[m_len >> 1u] = 0.0;
        double lastValue;
        for (int i = 1; i < (m_len >> 1u); i++)
        {
            lastValue = (0.414 / i) * .4;
            if (i % offset == 0)
                lastValue += TableCreatorHelper::getNextRand () * 0.5;

            m_freqWaveRe[i] = lastValue;
            m_freqWaveRe[m_len - i] = -m_freqWaveRe[i];
        }
    }

    void SynthOne::startCreation ()
    {
        auto sOne = SynthOne ();
        sOne.m_index = WaveForms::SYNTH_ONE;
        TableCreatorHelper::createTable (sOne);
    }

    void SynthTwo::generate ()
    {
        std::srand ((unsigned) 306);
        int offset = static_cast<int>(m_len) / 96;
        m_freqWaveRe[0] = m_freqWaveRe[m_len >> 1u] = 0.0;
        double lastValue;
        for (int i = 1; i < (m_len >> 1u); i++)
        {
            lastValue = 0.5 / 1.0 / i;
            if (i % offset == 0)
                lastValue += TableCreatorHelper::getNextRand () * 0.05;

            m_freqWaveRe[i] = lastValue;
            m_freqWaveRe[m_len - i] = -m_freqWaveRe[i];
        }
    }

    void SynthTwo::startCreation ()
    {
        auto sTwo = SynthTwo ();
        sTwo.m_index = WaveForms::SYNTH_TWO;
        TableCreatorHelper::createTable (sTwo);
    }

    void VeNoX::generate ()
    {
        std::srand ((unsigned) 3051);
        m_freqWaveRe[0] = m_freqWaveRe[m_len >> 1u] = 0.0;
        for (int i = 1; i < (m_len >> 1u); i++)
        {
            double val = TableCreatorHelper::getNextRand () * TableCreatorHelper::getNextRand ();
            if (i % 256 == 0)
                val += .3;
            m_freqWaveRe[i] = Utils::clamp(val / i, -1, 1);
            m_freqWaveRe[m_len - i] = -m_freqWaveRe[i];
        }
    }

    void VeNoX::startCreation ()
    {
        auto veNox = VeNoX ();
        veNox.m_index = WaveForms::VENOX;
        TableCreatorHelper::createTable (veNox);
    }
}