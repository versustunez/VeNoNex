#include "WaveformControl.h"
#include "../../../Core/Config.h"
#include "../../../Utils.h"

namespace VeNo
{
    WaveformControl::WaveformControl (const std::string& name, const std::string& pid)
            : BaseComponent (pid), m_name (name)
    {
        m_baseForm = std::make_unique<VeNoSelect> (m_name + "__waveform_base", m_processId);
        m_baseForm->init ("Primary Wave", LabelPosition::TOP, VeNoSelect::Type::WaveTable);
        m_secondForm = std::make_unique<VeNoSelect> (m_name + "__waveform_sec", m_processId);
        m_secondForm->init ("Secondary Wave", LabelPosition::TOP, VeNoSelect::Type::WaveTable);
        m_mixKnob = std::make_unique<VeNoKnob> (m_name + "__waveform_mix", m_processId);
        m_mixKnob->init ("Waveform Mix");

        addAndMakeVisible (*m_baseForm);
        addAndMakeVisible (*m_secondForm);
        addAndMakeVisible (*m_mixKnob);
    }

    void WaveformControl::resized ()
    {
        auto size = Utils::getScaledSize (11.0f);
        auto newHeight = getHeight () - size;
        auto secondHeight = newHeight / 3;
        m_baseForm->setBounds (0, size, getWidth (), secondHeight);
        m_secondForm->setBounds (0, m_baseForm->getY () + secondHeight, getWidth (), secondHeight);
        m_mixKnob->setBounds (0, m_secondForm->getY () + secondHeight, getWidth (), secondHeight);
    }

    void WaveformControl::paint (Graphics& g)
    {
        auto theme = Config::getInstance ()->getCurrentTheme ();
        auto size = static_cast<int>(Utils::setFontSize (11.0f, g));
        g.setColour (theme->getColour (ThemeColour::bg));
        Utils::drawRectangleWithRadius (0, 0, getWidth (), getHeight (), Utils::getScaledSize (10), g);
        g.setColour (theme->getColour (ThemeColour::font));
        g.drawText ("WaveformControl", 0, 0, getWidth (), size, juce::Justification::centred, true);
    }
}