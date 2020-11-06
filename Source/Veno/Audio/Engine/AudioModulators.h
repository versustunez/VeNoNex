#pragma once

#include <vector>
#include "Modulator.h"
#include "../Oscillator/VeNoEnvelope.h"

namespace VeNo
{
    struct MultiEnvelope
    {
        std::string name;
        std::vector<VeNoEnvelope*> envelopes;
    };
    enum EnvelopeType
    {
        Voices = 0,
        Free = 1
    };

    class AudioModulators
    {
    public:
        AudioModulators (const std::string& processId);

        ~AudioModulators ();

        void init ();

        void updateSampleRate (double sRate);

        std::vector<MultiEnvelope*> m_envelopes;

    protected:
        std::vector<Modulator*> m_modulators;
        std::string m_pid;
    };
}