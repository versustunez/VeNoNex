//
// Created by versustune on 13.06.20.
//

#include "Sidebar.h"
#include "VenoLogo.h"
#include "../../../Utils.h"

Sidebar::Sidebar (const std::string& processId) : BaseComponent(processId)
{
    m_lcd = std::make_unique<SidebarLCD>(processId);
    m_configButton = std::make_unique<VenoConfigButton>(processId);
    addAndMakeVisible(*m_lcd);
    addAndMakeVisible(*m_configButton);
}

Sidebar::~Sidebar ()
{
    m_lcd.reset(nullptr);
    m_configButton.reset(nullptr);
    m_mixer.reset(nullptr);
    VenoLogo::deleteInstance();
}

void Sidebar::resized ()
{
    if (m_lcd != nullptr)
    {
        m_lcd->setBounds(0, (getWidth() / 5) + 30, getWidth(), VeNo::Utils::getCalculatedHeight(175));
    }
    if (m_configButton != nullptr)
    {
        auto height = VeNo::Utils::getCalculatedHeight(30);
        auto margin = VeNo::Utils::getCalculatedWidth(10);
        m_configButton->setBounds(margin, getHeight()-height-margin, (getWidth()/2)-(margin*2), height);
    }
}

void Sidebar::paint (Graphics& g)
{
    auto logo = VenoLogo::getLogo();
    if (logo.isValid())
    {
        int height = getWidth() / 5;
        g.drawImage(logo, 0, 15, getWidth(), height, 0, 0, 500, 100);
    }
    else
    {
        g.setFont(getWidth() / 4);
        g.drawSingleLineText("VeNo", 0, 25);
    }
}

std::shared_ptr<Waveforms> Sidebar::getWaveform()
{
    return m_lcd->getWaveform();
}
