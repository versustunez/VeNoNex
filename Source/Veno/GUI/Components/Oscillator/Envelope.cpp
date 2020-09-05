#include "Envelope.h"
#include "../../../Utils.h"
#include "../../../Core/Config.h"

namespace VeNo
{
    Envelope::Envelope (const std::string& name, const std::string& pid)
            : BaseComponent (pid), m_name (name),
              m_attack (std::make_unique<VeNoKnob> (m_name + "__attack", m_processId)),
              m_decay (std::make_unique<VeNoKnob> (m_name + "__decay", m_processId)),
              m_sustain (std::make_unique<VeNoKnob> (m_name + "__sustain", m_processId)),
              m_release (std::make_unique<VeNoKnob> (m_name + "__release", m_processId))
    {
        m_attack->init ("Attack");
        m_decay->init ("Decay");
        m_sustain->init ("Sustain");
        m_release->init ("Release");

        addAndMakeVisible(*m_attack);
        addAndMakeVisible(*m_decay);
        addAndMakeVisible(*m_sustain);
        addAndMakeVisible(*m_release);
    }

    void Envelope::resized ()
    {
        auto size = Utils::getScaledSize (12.0f);
        auto width = getWidth () / 4;
        auto height = getHeight () - size;
        m_attack->setBounds (0, size, width, height);
        m_decay->setBounds (width, size, width, height);
        m_sustain->setBounds (width * 2, size, width, height);
        m_release->setBounds (width * 3, size, width, height);
    }

    void Envelope::paint (Graphics& g)
    {
        auto theme = Config::getInstance ()->getCurrentTheme ();
        auto size = static_cast<int>(Utils::setFontSize (11.0f, g));
        g.setColour (theme->getColour (ThemeColour::bg));
        Utils::drawRectangleWithRadius (0, 0, getWidth (), getHeight (), Utils::getScaledSize (10), g);
        g.setColour (theme->getColour (ThemeColour::font));
        g.drawText ("Envelopes", 0, 0, getWidth (), size, juce::Justification::centred, true);
    }
}