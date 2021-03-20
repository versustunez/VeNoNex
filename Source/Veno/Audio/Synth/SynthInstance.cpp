#include "SynthInstance.h"
#include "../../VenoInstance.h"

namespace VeNo::Synth
{
    Synthesizer::Synthesizer (std::string processId)
            : m_processId (std::move (processId))
    {
    }

    Synthesizer::~Synthesizer () = default;

    void
    Synthesizer::render (AudioBuffer<float>& buffer, const MidiBuffer& midiMessages, int startSample, int numSamples)
    {
        if (!m_isInit)
        {
            init ();
            return;
        }
        const ScopedLock sl (lock);
        const int targetChannels = buffer.getNumChannels ();
        auto midiIterator = midiMessages.findNextSamplePosition (startSample);
        if (targetChannels == 0)
        {
            return;
        }
        MidiMessage midi;
        bool firstEvent = true;
        for (; numSamples > 0; ++midiIterator)
        {
            if (midiIterator == midiMessages.cend ())
            {
                renderVoice (buffer, startSample, numSamples);
                return;
            }

            const auto metadata = *midiIterator;
            const int samplesToNextMidiMessage = metadata.samplePosition - startSample;
            if (samplesToNextMidiMessage >= numSamples)
            {
                renderVoice (buffer, startSample, numSamples);
                handleMidiEvent ((metadata.getMessage ()));
                break;
            }

            if (samplesToNextMidiMessage < (firstEvent ? 1 : 8))
            {
                handleMidiEvent (metadata.getMessage ());
                continue;
            }

            firstEvent = false;
            renderVoice (buffer, startSample, samplesToNextMidiMessage);
            handleMidiEvent (metadata.getMessage ());
            startSample += samplesToNextMidiMessage;
            numSamples -= samplesToNextMidiMessage;
        }
        std::for_each (midiIterator,
                       midiMessages.cend (),
                       [&] (const MidiMessageMetadata& meta)
                       { handleMidiEvent (meta.getMessage ()); });
    }

    void Synthesizer::setSampleRate (double sampleRate)
    {
        if (!m_isInit)
        {
            init ();
        }
        m_sampleRate = sampleRate;
        for (auto& m_voice : m_voices)
        {
            m_voice->updateSampleRate ();
        }
    }

    void Synthesizer::noteOn (int midiChannel, int midiNoteNumber, float velocity)
    {
        auto instance = VenoInstance::getInstance (m_processId);
        auto envs = instance->modulators->m_envelopes;
        for (int i = 0; i < m_voices.size (); i++)
        {
            auto& m_voice = m_voices[i];
            if (m_voice->getCurrentChannel () == midiChannel && m_voice->getCurrentNote () == midiNoteNumber)
            {
                envs[EnvelopeType::Voices]->envelopes[i]->noteOff ();
                m_voice->stopNote (1.0f);
            }
        }
        int index = 0;
        int voiceToSteal = -1;
        int highestNote = -1;
        auto legato = instance->handler->getParameter ("mono_legato")->getAsBoolean ();
        for (int i = 0; i < m_voices.size (); i++)
        {
            auto& m_voice = m_voices[i];
            if (m_voice->canPlay ())
            {
                m_voice->m_noteOnTime = ++m_lastNoteOnCounter;
                m_voice->startNote (midiChannel, midiNoteNumber, velocity, false);
                envs[EnvelopeType::Free]->envelopes[0]->noteOn ();
                envs[EnvelopeType::Voices]->envelopes[i]->noteOn ();
                voiceToSteal = -1;
                m_hasActiveNote = true;
                break;
            }
            if (legato)
            {
                voiceToSteal = index;
                m_lastNoteOnCounter = 0;
                m_hasActiveNote = true;
                break;
            }
            if (m_voice->getCurrentNote () > highestNote)
            {
                if (voiceToSteal == -1 ||m_voice->m_noteOnTime < m_voices[voiceToSteal]->m_noteOnTime)
                {
                    voiceToSteal = index;
                }
            }
            index++;
        }

        if (voiceToSteal != -1)
        {
            if (!legato)
            {
                m_voices[voiceToSteal]->stopNote (0.0f);
                m_voices[voiceToSteal]->m_noteOnTime = ++m_lastNoteOnCounter;
            }
            envs[EnvelopeType::Voices]->envelopes[voiceToSteal]->noteOn ();
            envs[EnvelopeType::Free]->envelopes[0]->noteOn ();
            m_voices[voiceToSteal]->startNote (midiChannel, midiNoteNumber, velocity, legato);
            m_hasActiveNote = true;
        }
    }

    void Synthesizer::noteOff (int midiChannel, int midiNoteNumber, float velocity)
    {
        auto instance = VenoInstance::getInstance (m_processId);
        auto envs = instance->modulators->m_envelopes;
        envs[EnvelopeType::Free]->envelopes[0]->noteOff ();
        m_hasActiveNote = false;
        for (int i = 0; i < m_voices.size (); i++)
        {
            auto& m_voice = m_voices[i];
            if (m_voice->getCurrentChannel () == midiChannel && m_voice->getCurrentNote () == midiNoteNumber)
            {
                envs[EnvelopeType::Voices]->envelopes[i]->noteOff ();
                m_voice->stopNote (1.0f);
            } else {
                if (m_voice->m_isActive) {
                    m_hasActiveNote = true;
                }
            }
        }
    }

    void Synthesizer::handleMidiEvent (const MidiMessage& m)
    {
        const int channel = m.getChannel ();
        if (m.isNoteOn ())
        {
            noteOn (channel, m.getNoteNumber (), m.getFloatVelocity ());
        }
        else if (m.isNoteOff ())
        {
            noteOff (channel, m.getNoteNumber (), m.getFloatVelocity ());
        }
        else if (m.isAllNotesOff () || m.isAllSoundOff ())
        {
            auto instance = VenoInstance::getInstance (m_processId);
            auto envs = instance->modulators->m_envelopes;
            envs[EnvelopeType::Free]->envelopes[0]->noteOff ();
            for (int i = 0; i < m_voices.size (); i++)
            {
                auto& m_voice = m_voices[i];
                envs[EnvelopeType::Voices]->envelopes[i]->noteOff ();
                m_voice->stopNote (1.0f);
            }
            m_lastNoteOnCounter = 0;
        }
        else if (m.isPitchWheel ())
        {
            const int wheelPos = m.getPitchWheelValue ();
            handlePitchWheel (wheelPos);
        }
    }

    void Synthesizer::handlePitchWheel (const int pos)
    {
        double realValue = (((double) pos / 16383) * 2) - 1;
        VenoInstance::getInstance (m_processId)->handler->setParameterValue ("pitch__wheel", realValue);
    }

    void Synthesizer::init ()
    {
        if (m_isInit)
        {
            return;
        }
        for (int i = 0; i < 5; ++i)
        {
            m_voices.push_back (std::make_unique<Voice> (i, m_processId));
        }
        getVariables();
        m_isInit = true;
    }

    void Synthesizer::renderVoice (AudioBuffer<float>& buffer, int startSample, int numSamples)
    {
        if (!master) {
           getVariables();
        }
        auto veNoBuffer = audioBuffer;
        bool leg = legato->m_value > 0.5;
        while (--numSamples >= 0)
        {
            matrix->updateSlots (m_hasActiveNote);
            output[0] = 0;
            output[1] = 0;
            output[2] = 0;
            int vIndex = 0;
            for (auto& voice : m_voices)
            {
                if (vIndex != 0 && leg)
                    break;
                vIndex++;
                if (!voice->m_isActive)
                    continue;
                bool cleanNote = true;
                bool runIntoSample = false;
                double values[3] = {0,0,0};
                for (int i = 0; i < voice->m_count; i++)
                {
                    auto envelope = voice->m_envelopes[i];
                    if (envelope->isActive () && envelope->m_value > 0)
                    {
                        auto osc = voice->m_oscillators[i];
                        cleanNote = false;
                        auto envValue = envelope->m_value;
                        if (osc->renderOsc ())
                        {
                            runIntoSample = true;
                            values[1] += osc->m_values[1] * envValue;
                            values[2] += osc->m_values[2] * envValue;
                        }
                        envelope->update ();
                    }
                }
                if (cleanNote || !runIntoSample)
                    voice->clear ();
                output[1] += (values[1] * voice->m_velocity * 0.25);
                output[2] += (values[2] * voice->m_velocity * 0.25);
            }
            output[1] *= master->m_value;
            output[2] *= master->m_value;
            buffer.addSample (0, startSample, output[1]);
            buffer.addSample (1, startSample, output[2]);
            veNoBuffer->addMonoSample(output[1]);
            veNoBuffer->addLeftSample(output[1]);
            veNoBuffer->addRightSample(output[2]);
            ++startSample;
        }
    }

    void Synthesizer::getVariables ()
    {
        auto instance = VenoInstance::getInstance (m_processId);
        matrix = instance->matrix;
        legato = instance->handler->getParameter ("mono_legato");
        master = instance->handler->getParameter ("master__volume");
        audioBuffer = instance->audioBuffer;
    }
}