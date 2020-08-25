#include "Theme.h"
#include "ThemePresets.cpp"
#include "../../Core/Config.h"

Theme::Theme (std::shared_ptr<PropertiesFile> file)
{
    m_configFile = file;
}

Theme::~Theme ()
{
    m_colours.clear();
    m_configFile.reset();
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
    m_configFile->setValue(ThemeColourToString(index), colour->toString());
    m_configFile->setNeedsToBeSaved(true);

}

void Theme::init ()
{
    getColourFromConfig(ThemeColour::bg);
    getColourFromConfig(ThemeColour::bg_two);
    getColourFromConfig(ThemeColour::accent);
    getColourFromConfig(ThemeColour::accent_two);
    getColourFromConfig(ThemeColour::warning);
    getColourFromConfig(ThemeColour::clip);
    getColourFromConfig(ThemeColour::lcd_bg);
    getColourFromConfig(ThemeColour::lcd);
}

void Theme::getColourFromConfig (ThemeColour index)
{
    std::string key = ThemeColourToString(index);
    if (m_configFile->containsKey(key))
    {
        auto baseColour = Colour::fromString(m_configFile->getValue(key));
        auto* colour = new Colour(baseColour.getRed(), baseColour.getGreen(), baseColour.getBlue());
        delete m_colours[index];
        m_colours[index] = colour;
    }
    else
    {
        // should only trigger if config is broken or empty :)
        setLEDTheme(this);
    }
}

Colour Theme::getColour (ThemeColour index)
{
    if (m_colours[index] != nullptr)
    {
        return *m_colours[index];
    }
    return Colour(255, 255, 255);
}

void Theme::setColourThemeById (int id)
{
    switch (id)
    {
        case 1:
            setLEDTheme(this);
            break;
        case 2:
            setOrangeDreamTheme(this);
            break;
        case 3:
            setBloodTheme(this);
            break;
        case 4:
            setOceanTheme(this);
        default:
            break;
    }
}

void Theme::setDefault (const std::string& value)
{
    if (value == "LED")
    {
        setLEDTheme(this);
    }
    if (value == "Blood")
    {
        setBloodTheme(this);
    }
    if (value == "Orange Dream")
    {
        setOrangeDreamTheme(this);
    }
    if (value == "Ocean")
    {
        setOceanTheme(this);
    }
    Config::getInstance()->repaintAll();
}
