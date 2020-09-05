#include "SiderbarMixerItem.h"
#include "../../../Utils.h"
#include "../../../Core/Config.h"

SidebarMixerItem::SidebarMixerItem (const std::string& pid, int index)
        : BaseComponent (pid), m_index (index), m_name ("osc" + std::to_string (index + 1)),
          m_text ("OSC " + std::to_string (index + 1)),
          m_onOffSwitch (std::make_unique<VeNoCheck> (m_name + "__active", "", pid)),
          m_levelKnob (std::make_unique<VeNoKnob> (m_name + "__level", pid))
{
    m_levelKnob->init ("Volume");

    addAndMakeVisible (*m_onOffSwitch);
    addAndMakeVisible (*m_levelKnob);
}

SidebarMixerItem::~SidebarMixerItem ()
{
    m_levelKnob.reset ();
    m_onOffSwitch.reset ();
}

void SidebarMixerItem::resized ()
{
    auto height = VeNo::Utils::getCalculatedHeight (30);
    auto width = VeNo::Utils::getCalculatedWidth (10);
    m_onOffSwitch->setBounds (width, height, getWidth () - (width * 2), height);
    m_levelKnob->setBounds (width, height * 2.5, getWidth () - (width * 2), getWidth ());
}

void SidebarMixerItem::paint (Graphics& g)
{
    auto theme = Config::getInstance ()->getCurrentTheme ();
    if ((m_index & 1) == 1)
        g.setColour (theme->getColour (ThemeColour::bg_two).withAlpha (0.2f));
    else
        g.setColour (theme->getColour (ThemeColour::bg));
    g.fillAll ();
    g.setColour (theme->getColour (ThemeColour::font));
    auto spacer = VeNo::Utils::setFontSize (13.0f, g);
    g.drawText (m_text, 0, spacer, getWidth (), VeNo::Utils::getCalculatedHeight (15), Justification::centred, true);
}