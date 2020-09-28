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

            if (samplesToNextMidiMessage < 1)
            {
                handleMidiEvent (metadata.getMessage ());
                continue;
            }

            renderVoice (buffer, startSample, samplesToNextMidiMessage);
            handleMidiEvent (metadata.getMessage ());
            startSample += samplesToNextMidiMessage;
            numSamples -= samplesToNextMidiMessage;
        }
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


    bool Synthesizer::isInit () const
    {
        return m_isInit;
    }

    void Synthesizer::noteOn (int midiChannel, int midiNoteNumber, float velocity)
    {
        for (auto& m_voice : m_voices)
        {
            if (m_voice->getCurrentChannel () == midiChannel && m_voice->getCurrentNote () == midiNoteNumber)
            {
                m_voice->stopNote (1.0f);
            }
        }
        int index = 0;
        int voiceToSteal = -1;
        int highestNote = -1;
        for (auto& m_voice : m_voices)
        {
            if (m_voice->canPlay ())
            {
                m_voice->m_noteOnTime = ++m_lastNoteOnCounter;
                m_voice->startNote (midiChannel, midiNoteNumber, velocity);
                voiceToSteal = -1;
                break;
            }
            if (m_voice->getCurrentNote () > highestNote)
            {
                if (voiceToSteal == -1)
                {
                    voiceToSteal = index;
                }
                else if (m_voice->m_noteOnTime < m_voices[voiceToSteal]->m_noteOnTime)
                {
                    voiceToSteal = index;
                }
            }
            index++;
        }

        if (voiceToSteal != -1)
        {
            m_voices[voiceToSteal]->stopNote (0.0f);
            m_voices[voiceToSteal]->m_noteOnTime = ++m_lastNoteOnCounter;
            m_voices[voiceToSteal]->startNote (midiChannel, midiNoteNumber, velocity);
        }
    }

    void Synthesizer::noteOff (int midiChannel, int midiNoteNumber, float velocity)
    {
        for (auto& m_voice : m_voices)
        {
            if (m_voice->getCurrentChannel () == midiChannel && m_voice->getCurrentNote () == midiNoteNumber)
            {
                m_voice->stopNote (1.0f);
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
            for (auto& m_voice : m_voices)
            {
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
        m_isInit = true;
    }

    void Synthesizer::renderVoice (AudioBuffer<float>& buffer, int startSample, int numSamples)
    {
        while (--numSamples >= 0)
        {
            VenoInstance::getInstance (m_processId)->matrix->updateSlots ();
            output[0] = 0;
            output[1] = 0;
            output[2] = 0;
            for (auto& voice : m_voices)
            {
                if (!voice->m_isActive)
                {
                    continue;
                }
                bool cleanNote = true;
                bool runIntoSample = false;
                for (int i = 0; i < voice->m_count; i++)
                {
                    if (voice->m_envelopes[i]->isActive ())
                    {
                        cleanNote = false;
                        voice->m_envelopes[i]->update ();
                        auto envValue = voice->m_envelopes[i]->getValue ();
                        if (voice->m_oscillators[i]->render ())
                        {
                            runIntoSample = true;
                            output[0] += voice->m_oscillators[i]->getMonoValue () * envValue;
                            output[1] += voice->m_oscillators[i]->getLeftValue () * envValue;
                            output[2] += voice->m_oscillators[i]->getRightValue () * envValue;
                        };
                    }
                }
                if (cleanNote || !runIntoSample)
                {
                    voice->clear ();
                }
            }
            int channelCount = buffer.getNumChannels ();
            if (channelCount == 1)
            {
                output[0] *= 0.25;
                buffer.addSample (0, startSample, output[0]);
            }
            else
            {
                output[1] *= 0.25;
                output[2] *= 0.25;
                buffer.addSample (0, startSample, output[1]);
                buffer.addSample (1, startSample, output[2]);
            }
            ++startSample;
        }
    }
}