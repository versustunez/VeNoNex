#include "Unison.h"
#include "../../../Core/Config.h"
#include "../../../Utils.h"

namespace VeNo
{
    Unison::Unison (const std::string& name, const std::string& pid)
            : BaseComponent (pid),
              m_name (name)
    {
        m_modeSelector = std::make_unique<VeNoSelect> (name + "__detune_mode", m_processId);
        m_modeSelector->init ("Mode", LabelPosition::TOP, VeNoSelect::Type::DetuneMode);
        m_amount = std::make_unique<VeNoKnob> (name + "__detune_amount", m_processId);
        m_amount->init ("Volume");
        m_dense = std::make_unique<VeNoKnob> (name + "__detune_dense", m_processId);
        m_dense->init ("Density");
        m_stereo = std::make_unique<VeNoKnob> (name + "__stereo", m_processId);
        m_stereo->init ("Stereo");
        m_voices = std::make_unique<VeNoKnob> (name + "__voices", m_processId);
        m_voices->init ("Voices");

        addAndMakeVisible (*m_modeSelector);
        addAndMakeVisible (*m_amount);
        addAndMakeVisible (*m_dense);
        addAndMakeVisible (*m_stereo);
        addAndMakeVisible (*m_voices);
    }

    void Unison::resized ()
    {
        auto size = Utils::getScaledSize (20.0f);
        auto newHeight = getHeight () - size;
        auto ySpace = size;
        if (newHeight > 100)
        {
            ySpace += (newHeight - 100) - 50;
            newHeight = 100;
        }
        auto width = getWidth () * 0.35;
        auto lastWidth = (getWidth () * 0.65) / 4;
        m_modeSelector->setBounds (0, ySpace, width, newHeight);
        m_voices->setBounds (width, ySpace, lastWidth, newHeight);
        m_stereo->setBounds (width + lastWidth, ySpace, lastWidth, newHeight);
        m_dense->setBounds (width + (lastWidth * 2), ySpace, lastWidth, newHeight);
        m_amount->setBounds (width + (lastWidth * 3), ySpace, lastWidth, newHeight);
    }

    void Unison::paint (Graphics& g)
    {
        auto theme = Config::getInstance ()->getCurrentTheme ();
        auto size = static_cast<int>(Utils::setFontSize (13.0f, g));
        g.setColour (theme->getColour (ThemeColour::bg));
        Utils::drawRectangleWithRadius (0, 0, getWidth (), getHeight (), Utils::getScaledSize (10), g);
        g.setColour (theme->getColour (ThemeColour::font));
        g.drawText ("Unison", 0, 0, getWidth (), size, juce::Justification::centred, true);
    }
}