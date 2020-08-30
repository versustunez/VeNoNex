#include "Theme.h"
#include "../../Core/Config.h"
#include "ThemePresets.h"

Theme::Theme (std::shared_ptr<PropertiesFile> file)
{
    m_configFile = file;
}

Theme::~Theme ()
{
    m_colours.clear ();
    m_configFile.reset ();
}

void Theme::setColour (ThemeColour index, Colour* colour)
{
    auto c = m_colours[index];
    if (c)
    {
        delete c;
        m_colours[index] = colour;
    }
    else
    {
        m_colours[index] = colour;
    }
    m_configFile->setValue (ThemePresets::ThemeColourToString (index), colour->toString ());
    m_configFile->setNeedsToBeSaved (true);

}

void Theme::init ()
{
    getColourFromConfig (ThemeColour::bg);
    getColourFromConfig (ThemeColour::bg_two);
    getColourFromConfig (ThemeColour::accent);
    getColourFromConfig (ThemeColour::accent_two);
    getColourFromConfig (ThemeColour::font);
    getColourFromConfig (ThemeColour::clip);
    getColourFromConfig (ThemeColour::lcd_bg);
    getColourFromConfig (ThemeColour::lcd);
}

void Theme::getColourFromConfig (ThemeColour index)
{
    std::string key = ThemePresets::ThemeColourToString (index);
    if (m_configFile->containsKey (key))
    {
        auto baseColour = Colour::fromString (m_configFile->getValue (key));
        auto* colour = new Colour (baseColour.getRed (), baseColour.getGreen (), baseColour.getBlue ());
        delete m_colours[index];
        m_colours[index] = colour;
    }
    else
    {
        // should only trigger if config is broken or empty :)
        ThemePresets::setLEDTheme (this);
    }
}

Colour Theme::getColour (ThemeColour index)
{
    if (m_colours[index] != nullptr)
    {
        return *m_colours[index];
    }
    return Colour (255, 255, 255);
}

void Theme::setColourThemeById (int id)
{
    switch (id)
    {
        case 1:
            ThemePresets::setLEDTheme (this);
            break;
        case 2:
            ThemePresets::setOrangeDreamTheme (this);
            break;
        case 3:
            ThemePresets::setBloodTheme (this);
            break;
        case 4:
            ThemePresets::setOceanTheme (this);
            break;
        case 5:
            ThemePresets::setGirlTheme(this);
            break;
        default:
            break;
    }
}

void Theme::setDefault (const std::string& value)
{
    if (value == "LED")
    {
        ThemePresets::setLEDTheme (this);
    }
    if (value == "Blood")
    {
        ThemePresets::setBloodTheme (this);
    }
    if (value == "Orange Dream")
    {
        ThemePresets::setOrangeDreamTheme (this);
    }
    if (value == "Ocean")
    {
        ThemePresets::setOceanTheme (this);
    }
    if (value == "Girl")
    {
        ThemePresets::setGirlTheme(this);
    }
    Config::getInstance ()->repaintAll ();
}
