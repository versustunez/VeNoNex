#include "SynthInstance.h"
#include "VenoVoice.h"
#include "VenoSound.h"
#include <utility>

SynthInstance::SynthInstance (std::string processId)
        : m_processId (std::move (processId))
{
}

SynthInstance::~SynthInstance ()
{
    m_synth.removeSound (0);
    for (int i = 0; i < 5; ++i)
    {
        m_synth.removeVoice (i);
    }
}


void SynthInstance::render (AudioBuffer<float>& buffer, const MidiBuffer& midiMessages, int startSample, int numSamples)
{
    m_synth.renderNextBlock (buffer, midiMessages, startSample, numSamples);
}

void SynthInstance::setSampleRate (double sampleRate)
{
    m_synth.setCurrentPlaybackSampleRate(sampleRate);
    m_sampleRate = sampleRate;
    if (!m_isInit) {
        for (int p = 0; p < 5; p++)
        {
            m_synth.addVoice (new VenoVoice (p, sampleRate, m_processId));
        }
        m_synth.addSound (new VenoSound ());
        m_isInit = true;
    }
}


bool SynthInstance::isInit () const
{
    return m_isInit;
}

void SynthInstance::noteOn (int midiChannel, int midiNoteNumber, float velocity)
{
    m_synth.noteOn(midiChannel, midiNoteNumber, velocity);
}

void SynthInstance::noteOff (int midiChannel, int midiNoteNumber, float velocity)
{
    m_synth.noteOff(midiChannel, midiNoteNumber, velocity, true);
}
