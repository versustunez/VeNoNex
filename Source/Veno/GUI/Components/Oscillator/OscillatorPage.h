#pragma once

#include "../BaseComponent.h"
#include "Unison.h"
#include "WaveformControl.h"
#include "GUILimiter.h"
#include "Envelope.h"
#include "Pitch.h"

namespace VeNo
{
    /**
     * Class that Holds everything a Oscillator can use! It's not for the LFO
     * Waveform, Unison, Envelope, Pitch, OSC-Main (Phase, Random-Phase, Pan), Limiter
     */
    class OscillatorPage : public BaseComponent
    {
    public:
        OscillatorPage(const std::string& name, const std::string& pid);
        ~OscillatorPage() override = default;

        void resized () override;

        void paint (Graphics& g) override;

    protected:
        std::unique_ptr<Unison> m_unison;
        std::unique_ptr<WaveformControl> m_waveformCtrl;
        std::unique_ptr<GUILimiter> m_limiter;
        std::unique_ptr<Envelope> m_envelope;
        std::unique_ptr<Pitch> m_pitch;
    };
}