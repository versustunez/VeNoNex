#include "Sidebar.h"
#include "VenoLogo.h"
#include "../../../Utils.h"

Sidebar::Sidebar (const std::string& processId) : BaseComponent (processId),
                                                  m_lcd (std::make_unique<SidebarLCD> (processId)),
                                                  m_mixer (std::make_unique<SidebarMixer> (processId)),
                                                  m_modMixer(std::make_unique<ModMixer>(processId)),
                                                  m_volumeKnob(std::make_unique<VeNoKnob> ("master__volume", processId)),
                                                  m_preset(std::make_unique<PresetManagerComponent> (processId))
{
    m_volumeKnob->init ("Synth Volume");
    addAndMakeVisible (*m_lcd);
    addAndMakeVisible (*m_mixer);
    addAndMakeVisible (*m_modMixer);
    addAndMakeVisible (*m_volumeKnob);
    addAndMakeVisible (*m_preset);
}

Sidebar::~Sidebar ()
{
    m_lcd.reset (nullptr);
    m_mixer.reset (nullptr);
    m_volumeKnob.reset (nullptr);
    m_modMixer.reset (nullptr);
    m_preset.reset (nullptr);
    VenoLogo::deleteInstance ();
}

void Sidebar::resized ()
{
    int topMargin = VeNo::Utils::getScaledSize (30);
    int ySpace = VeNo::Utils::getScaledSize (15);
    m_lcd->setBounds (0, (getWidth () / 5) + topMargin, getWidth (), VeNo::Utils::getScaledSize (175));
    m_preset->setBounds (0, m_lcd->getY () + m_lcd->getHeight (), getWidth (), VeNo::Utils::getScaledSize (30));
    m_mixer->setBounds (0, m_preset->getY () + m_preset->getHeight (), getWidth (),
                        VeNo::Utils::getScaledSize (165));
    m_volumeKnob->setBounds (0, m_mixer->getY () + m_mixer->getHeight () + ySpace, getWidth (),
                             VeNo::Utils::getScaledSize (110));
    m_modMixer->setBounds (0, m_volumeKnob->getY () + m_volumeKnob->getHeight () + ySpace, getWidth (),
                           VeNo::Utils::getScaledSize (100));
}

void Sidebar::paint (Graphics& g)
{
    auto logo = VenoLogo::getLogo ();
    if (logo.isValid ())
    {
        int topMargin = VeNo::Utils::getScaledSize (15);
        int height = getWidth () / 5;
        g.drawImage (logo, 0, topMargin, getWidth (), height, 0, 0, 500, 100);
    }
    else
    {
        int topMargin = VeNo::Utils::getScaledSize (25);
        g.setFont (getWidth () / 4);
        g.drawSingleLineText ("VeNo", 0, topMargin);
    }
}
