#include "ModMixer.h"
#include "../../../Utils.h"
#include "../../../Core/Config.h"

ModMixer::ModMixer (const std::string& pid) : BaseComponent (pid)
{
    m_modKnobs.resize (4);
    for (int i = 0; i < 4; ++i)
    {
        auto mod = "mod" + std::to_string (i + 1);
        m_modKnobs[i] = std::make_unique<VeNoKnob> (mod, m_processId);
        m_modKnobs[i]->init ("MOD " + std::to_string (i + 1));
        addAndMakeVisible (*m_modKnobs[i]);
    }
}

ModMixer::~ModMixer ()
= default;

void ModMixer::resized ()
{
    auto width = getWidth () / 4;
    auto x = 0;
    auto h = VeNo::Utils::getCalculatedHeight (15);
    auto w = VeNo::Utils::getCalculatedWidth (10);
    for (int i = 0; i < 4; ++i)
    {
        m_modKnobs[i]->setBounds (x + w, h, width - (w * 2), getHeight () - h);
        x += width;
    }
}

void ModMixer::paint (Graphics& g)
{
    auto h = VeNo::Utils::getCalculatedHeight (15);
    auto theme = Config::getInstance ()->getCurrentTheme ();
    VeNo::Utils::setFontSize (13, g);
    g.setColour (theme->getColour (ThemeColour::font));
    g.drawText ("MODS", 0, 0, getWidth (), h, Justification::centred, true);

}
