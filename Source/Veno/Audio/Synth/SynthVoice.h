#pragma once

#include <string>
#include <memory>
#include "JuceHeader.h"
#include "../Oscillator/SynthOscillator.h"
#include "../Oscillator/VeNoEnvelope.h"

namespace VeNo::Synth
{
    class Voice
    {
    public:
        Voice (int index, std::string id);

        ~Voice ();

        void startNote (int midiChannel, int midiNoteNumber, float velocity, bool isLegato);

        void stopNote (float velocity);

        void clear ();

        bool canPlay ();

        void updateSampleRate ();

        int getCurrentNote () const;

        int getCurrentChannel () const;

        bool isOlder (uint64_t time) const
        {
            return m_noteOnTime < time;
        }

        uint64_t m_noteOnTime = 0;
        bool m_isActive = false;
        int m_count = 4;

        std::vector<std::shared_ptr<VeNoEnvelope>> m_envelopes;
        std::vector<std::shared_ptr<SynthOscillator>> m_oscillators;
    protected:
        int m_index;
        std::string m_id;
        int m_currentNote = -1;
        int m_currentChannel = -1;
        float m_velocity = 0.0;
        double m_lastSampleRate = 0;
        bool m_isLegato = false;
    };
}