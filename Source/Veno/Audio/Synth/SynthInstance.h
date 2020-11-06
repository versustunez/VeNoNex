#pragma once

#include <string>
#include "JuceHeader.h"
#include "SynthVoice.h"

// class that hold all voices, oscillators and other stuff :)
namespace VeNo::Synth
{
    class Synthesizer
    {
    private:
        std::string m_processId;
        std::vector<std::unique_ptr<Voice>> m_voices;
        double m_sampleRate = -1;
        bool m_isInit = false;
    public:
        explicit Synthesizer (std::string processId);

        ~Synthesizer ();

        void render (AudioBuffer<float>& buffer, const MidiBuffer& midiMessages, int startSample, int numSamples);

        void setSampleRate (double sampleRate);

        void noteOn (int midiChannel, int midiNoteNumber, float velocity);

        void noteOff (int midiChannel, int midiNoteNumber, float velocity);

        void handleMidiEvent (const MidiMessage& m);

        void renderVoice (AudioBuffer<float>& buffer, int startSample, int numSamples);

    protected:
        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Synthesizer)

        void handlePitchWheel (int pos);

        void init ();

        uint64_t m_lastNoteOnCounter = 0;
        CriticalSection lock;
        double output[3] = {0, 0, 0};
    };
}