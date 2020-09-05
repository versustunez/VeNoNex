#include "OscillatorPage.h"
#include "../../../Utils.h"

namespace VeNo
{

    OscillatorPage::OscillatorPage (const std::string& name, const std::string& pid)
            : BaseComponent (pid),
              m_unison (std::make_unique<Unison> (name, m_processId)),
              m_waveformCtrl (std::make_unique<WaveformControl> (name, m_processId)),
              m_limiter (std::make_unique<GUILimiter> (name, m_processId)),
              m_envelope (std::make_unique<Envelope> (name, m_processId)),
              m_pitch (std::make_unique<Pitch> (name, m_processId))
    {
        addAndMakeVisible (*m_unison);
        addAndMakeVisible (*m_waveformCtrl);
        addAndMakeVisible (*m_limiter);
        addAndMakeVisible (*m_envelope);
        addAndMakeVisible (*m_pitch);
    }

    void OscillatorPage::resized ()
    {
        auto gap = Utils::getScaledSize(10);
        auto halfHeight = (getHeight () * 0.5);
        auto oneThirdHeight = (getHeight () / 3);
        auto oneFour = (getWidth () * 0.25);
        auto halfWidth = (getWidth () * 0.5);
        m_pitch->setBounds (0, 0, oneFour, halfHeight);
        m_limiter->setBounds (0, halfHeight, oneFour, halfHeight);
        m_envelope->setBounds (oneFour, 0, halfWidth, oneThirdHeight);
        m_waveformCtrl->setBounds (oneFour + halfWidth, 0, oneFour, oneThirdHeight + oneThirdHeight);
        m_unison->setBounds (oneFour, m_waveformCtrl->getHeight () + gap, getWidth () - oneFour - gap, oneThirdHeight);
    }

    void OscillatorPage::paint (Graphics& g)
    {
    }
}