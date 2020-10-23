#include "SynthVoice.h"
#include "../../Core/AudioConfig.h"
namespace VeNo::Synth
{
    Voice::Voice (int index, std::string id) :
            m_index (index), m_id (std::move (id))
    {
        m_lastSampleRate = AudioConfig::getInstance ()->getSampleRate ();
        for (int i = 0; i < m_count; i++)
        {
            auto name = "osc" + std::to_string (i + 1);
            m_oscillators.push_back(std::make_shared<SynthOscillator> (m_id, 9, name));
            m_oscillators[i]->setVoice (index);
            m_oscillators[i]->setIndex (index);
            m_envelopes.push_back(std::make_shared<VeNoEnvelope> (m_id, name, m_lastSampleRate));
            m_envelopes[i]->setVoice (index);
        }
    }

    Voice::~Voice () = default;

    void Voice::startNote (int midiChannel, int midiNoteNumber, float velocity, bool isLegato)
    {
        m_isActive = true;
        m_velocity = velocity;
        m_currentNote = midiNoteNumber;
        m_currentChannel = midiChannel;
        m_isLegato = isLegato;
        for (int i = 0; i < m_count; i++)
        {
            m_oscillators[i]->start (midiNoteNumber, isLegato && m_index == 0);
            m_envelopes[i]->prepare ();
            m_envelopes[i]->noteOn ();
        }
    }

    void Voice::stopNote (float velocity)
    {
        for (int i = 0; i < m_count; i++)
        {
            m_envelopes[i]->noteOff ();
            if (!m_envelopes[i]->isActive () || velocity == 0)
            {
                m_oscillators[i]->stop ();
                clear ();
            }
        }
    }

    void Voice::clear ()
    {
        m_currentChannel = -1;
        m_currentNote = -1;
        m_velocity = 0;
        m_isActive = false;
    }

    bool Voice::canPlay ()
    {
        return !m_isActive && m_currentNote == -1 && m_currentChannel == -1 && m_velocity == 0;
    }

    void Voice::updateSampleRate ()
    {
        double sRate = AudioConfig::getInstance ()->getSampleRate ();
        if (m_lastSampleRate != sRate)
        {
            m_lastSampleRate = sRate;
            for (int i = 0; i < m_count; i++)
            {
                m_envelopes[i]->setSampleRate (m_lastSampleRate);
            }
        }
    }

    int Voice::getCurrentNote () const
    {
        return m_currentNote;
    }

    int Voice::getCurrentChannel () const
    {
        return m_currentChannel;
    }
}