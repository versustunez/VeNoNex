#include "AudioModulators.h"
#include "../Oscillator/VeNoLFO.h"
#include "../../VenoInstance.h"
#include "ModModulator.h"

namespace VeNo
{
    AudioModulators::AudioModulators (const std::string& processId)
            : m_pid (processId)
    {

    }

    AudioModulators::~AudioModulators ()
    {
        for (auto & m_modulator : m_modulators)
        {
            delete m_modulator;
        }
        m_modulators.clear();
    }

    void AudioModulators::init ()
    {
        auto matrix = VenoInstance::getInstance (m_pid)->matrix;
        for (int i = 1; i <= 2; ++i)
        {
            std::string name = "lfo" + std::to_string (i);
            auto lfoOne = new VeNoLFO (m_pid, 9, name);
            lfoOne->m_showName = "LFO" + std::to_string(i);
            lfoOne->setIndex(0);
            lfoOne->setVoice(-1);
            lfoOne->m_isTwoSides = true;
            m_modulators.push_back (lfoOne);
            matrix->addModulator (name, lfoOne);
        }
        for (int i = 1; i <= 4; ++i)
        {
            std::string name = "mod" + std::to_string (i);
            auto mod = new ModModulator(name, "Mod" + std::to_string(i), m_pid);
            m_modulators.push_back (mod);
            matrix->addModulator (name, mod);
        }
    }
}