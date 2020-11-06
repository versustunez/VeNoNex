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
        for (auto& m_modulator : m_modulators)
        {
            delete m_modulator;
        }
        for (auto& m_envelope : m_envelopes)
        {
            for (auto& env : m_envelope->envelopes)
            {
                delete env;
            }
            delete m_envelope;
        }
        m_modulators.clear ();
        m_envelopes.clear ();
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
            auto mod = new ModModulator (name, "Mod" + std::to_string (i), m_pid);
            m_modulators.push_back (mod);
            matrix->addModulator (name, mod);
        }

        for (int i = 0; i < 2; ++i)
        {
            m_envelopes.push_back (new MultiEnvelope ());
            std::string name = "env" + std::to_string (i + 1);
            int count = i == 0 ? 5 : 1;
            m_envelopes[i]->name = name;
            for (int j = 0; j < count; ++j)
            {
                m_envelopes[i]->envelopes.push_back (new VeNoEnvelope (m_pid, name, 44100));
                m_envelopes[i]->envelopes[j]->setVoice (count == 1 ? -1 : j);
            }
        }

    }

    void AudioModulators::updateSampleRate (double sRate)
    {
        for (auto& m_envelope : m_envelopes)
        {
            for (auto& env : m_envelope->envelopes)
            {
                env->setSampleRate (sRate);
            }
        }
    }
}