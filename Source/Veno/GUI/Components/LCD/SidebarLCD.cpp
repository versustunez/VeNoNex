//
// Created by versustune on 11.06.20.
//

#include "SidebarLCD.h"
#include "../../../Utils.h"
#include "../../../Core/Config.h"
#include "../../../Fonts/Fonts.h"

SidebarLCD::SidebarLCD (const std::string& process_id) : BaseComponent(process_id)
{
    waveform = std::make_shared<Waveforms>(process_id);
    addAndMakeVisible(*waveform);
}

SidebarLCD::~SidebarLCD ()
{
    waveform.reset();
}

void SidebarLCD::drawHeadline (Graphics& g)
{
    float fontSize = VeNo::Utils::setFontSize(12.0f, g) + 2;
    int line = m_innerY + fontSize + 2;
    // should draw random stuff? or draw current selected preset :)
    g.drawText(">>> INIT <<<", 0, m_innerY, getWidth() - m_width, fontSize,
               Justification::centred,
               true);
    g.drawLine(0, line, getWidth(), line);
}

void SidebarLCD::drawFooter (Graphics& g)
{
    float fontSize = VeNo::Utils::setFontSize(8.0f, g) + 4;
    int space = m_innerY + fontSize;
    int line = getHeight() - space;
    g.drawText("by VersusTuneZ for " + SystemStats::getFullUserName(), 0, line, getWidth() - m_width, fontSize,
               Justification::horizontallyCentred,
               true);
    g.drawLine(0, line - 4, getWidth(), line - 4);
}

void SidebarLCD::resized ()
{
    float topSpace = (12 * Config::getInstance()->getScale()) + 4 + m_innerY;
    if (waveform != nullptr)
    {
        waveform->setBounds(0, topSpace * 2, getWidth(), getHeight() - (topSpace * 4));
    }
}

void SidebarLCD::paint (Graphics& g)
{
    std::shared_ptr<Theme> theme = Config::getInstance()->getCurrentTheme();
    auto colour = theme->getColour(ThemeColour::lcd_bg);
    g.fillAll(colour);
    // background
    auto accent = theme->getColour(ThemeColour::lcd);
    g.setColour(accent);
    g.setFont(*VenoFonts::getLCD());
    drawHeadline(g);
    drawFooter(g);
}

std::shared_ptr<Waveforms> SidebarLCD::getWaveform()
{
    return waveform;
}
