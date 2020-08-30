#include "ThemePresets.h"

/*
 * this file holds function that read some presets
 * in the current Theme class
 * so we doesn't have lot's of classes that only save some hex codes... and make the coding harder
 * also good on this is that the user can slightly change the preset m_theme and doesn't have to make all of them himself
 *
 * maybe i want a double m_look and feel... that's make it easier to implement different knob styles, slider styles and co
 */

void ThemePresets::setLEDTheme (Theme* theme)
{
    theme->setColour (ThemeColour::bg, new Colour (41, 47, 54));
    theme->setColour (ThemeColour::bg_two, new Colour (38, 38, 38));
    theme->setColour (ThemeColour::accent, new Colour (169, 208, 142));
    theme->setColour (ThemeColour::accent_two, new Colour (118, 183, 143));
    theme->setColour (ThemeColour::clip, new Colour (255, 23, 68));
    theme->setColour (ThemeColour::font, new Colour (255, 255, 255));
    theme->setColour (ThemeColour::lcd_bg, new Colour (21, 21, 21));
    theme->setColour (ThemeColour::lcd, new Colour (169, 208, 142));
}

void ThemePresets::setBloodTheme (Theme* theme)
{
    theme->setColour (ThemeColour::bg, new Colour (41, 47, 54));
    theme->setColour (ThemeColour::bg_two, new Colour (64, 67, 78));
    theme->setColour (ThemeColour::accent, new Colour (180, 38, 50));
    theme->setColour (ThemeColour::accent_two, new Colour (115, 47, 64));
    theme->setColour (ThemeColour::clip, new Colour (255, 23, 68));
    theme->setColour (ThemeColour::font, new Colour (255, 255, 255));
    theme->setColour (ThemeColour::lcd_bg, new Colour (43, 0, 0));
    theme->setColour (ThemeColour::lcd, new Colour (255, 0, 0));
}

void ThemePresets::setOrangeDreamTheme (Theme* theme)
{
    theme->setColour (ThemeColour::bg, new Colour (21, 21, 21));
    theme->setColour (ThemeColour::bg_two, new Colour (42, 42, 42));
    theme->setColour (ThemeColour::accent, new Colour (255, 160, 0));
    theme->setColour (ThemeColour::accent_two, new Colour (255, 11, 0));
    theme->setColour (ThemeColour::clip, new Colour (255, 23, 68));
    theme->setColour (ThemeColour::font, new Colour (255, 255, 255));
    theme->setColour (ThemeColour::lcd_bg, new Colour (33, 33, 33));
    theme->setColour (ThemeColour::lcd, new Colour (255, 160, 0));
}

void ThemePresets::setOceanTheme (Theme* theme)
{
    theme->setColour (ThemeColour::bg, new Colour (27, 27, 33));
    theme->setColour (ThemeColour::bg_two, new Colour (66, 67, 74));
    theme->setColour (ThemeColour::accent, new Colour (31, 115, 255));
    theme->setColour (ThemeColour::accent_two, new Colour (44, 40, 93));
    theme->setColour (ThemeColour::clip, new Colour (255, 23, 68));
    theme->setColour (ThemeColour::font, new Colour (255, 255, 255));
    theme->setColour (ThemeColour::lcd_bg, new Colour (0, 0, 0));
    theme->setColour (ThemeColour::lcd, new Colour (0, 129, 194));
}

void ThemePresets::setGirlTheme (Theme* theme)
{
    theme->setColour (ThemeColour::bg, new Colour (27, 27, 33));
    theme->setColour (ThemeColour::bg_two, new Colour (66, 67, 74));
    theme->setColour (ThemeColour::accent, new Colour (242, 94, 122));
    theme->setColour (ThemeColour::accent_two, new Colour (201, 90, 147));
    theme->setColour (ThemeColour::clip, new Colour (255, 23, 68));
    theme->setColour (ThemeColour::font, new Colour (255, 255, 255));
    theme->setColour (ThemeColour::lcd_bg, new Colour (0, 0, 0));
    theme->setColour (ThemeColour::lcd, new Colour (242, 94, 122));
}

std::string ThemePresets::ThemeColourToString (ThemeColour index)
{
    switch (index)
    {
        case ThemeColour::bg:
            return "colour_bg";
        case ThemeColour::bg_two:
            return "colour_bg_two";
        case ThemeColour::accent:
            return "colour_accent";
        case ThemeColour::accent_two:
            return "colour_accent_two";
        case ThemeColour::clip:
            return "colour_clip";
        case ThemeColour::font:
            return "colour_font";
        case ThemeColour::lcd_bg:
            return "colour_lcd_bg";
        case ThemeColour::lcd:
            return "colour_lcd";
        default:
            return "";
    }
}