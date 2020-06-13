#include "Theme.h"

/*
 * this file holds function that read some presets
 * in the current Theme class
 * so we doesn't have lot's of classes that only save some hex codes... and make the coding harder
 * also good on this is that the user can slightly change the preset m_theme and doesn't have to make all of them himself
 *
 * maybe i want a double m_look and feel... that's make it easier to implement different knob styles, slider styles and co
 */

void setLEDTheme(Theme *theme) {
    theme->setColour(ThemeColour::bg, new Colour(41, 47, 54));
    theme->setColour(ThemeColour::bg_two, new Colour(217, 217, 217));
    theme->setColour(ThemeColour::accent, new Colour(169, 208, 142));
    theme->setColour(ThemeColour::accent_two, new Colour(139, 171, 117));
    theme->setColour(ThemeColour::clip, new Colour(255, 23, 68));
    theme->setColour(ThemeColour::warning, new Colour(255, 143, 0));
    theme->setColour(ThemeColour::lcd_bg, new Colour(21, 21, 21));
    theme->setColour(ThemeColour::lcd, new Colour(169, 208, 142));
}

void setBloodTheme(Theme *theme) {
    theme->setColour(ThemeColour::bg, new Colour(41, 47, 54));
    theme->setColour(ThemeColour::bg_two, new Colour(64, 67, 78));
    theme->setColour(ThemeColour::accent, new Colour(180, 38, 50));
    theme->setColour(ThemeColour::accent_two, new Colour(115, 47, 64));
    theme->setColour(ThemeColour::clip, new Colour(255, 23, 68));
    theme->setColour(ThemeColour::warning, new Colour(255, 143, 0));
    theme->setColour(ThemeColour::lcd_bg, new Colour(0, 0, 0));
    theme->setColour(ThemeColour::lcd, new Colour(180, 38, 78));
}

void setOrangeDreamTheme(Theme *theme) {
    theme->setColour(ThemeColour::bg, new Colour(21, 21, 21));
    theme->setColour(ThemeColour::bg_two, new Colour(42, 42, 42));
    theme->setColour(ThemeColour::accent, new Colour(255, 160, 0));
    theme->setColour(ThemeColour::accent_two, new Colour(255, 11, 0));
    theme->setColour(ThemeColour::clip, new Colour(255, 23, 68));
    theme->setColour(ThemeColour::warning, new Colour(255, 143, 0));
    theme->setColour(ThemeColour::lcd_bg, new Colour(33, 33, 33));
    theme->setColour(ThemeColour::lcd, new Colour(255, 160, 0));
}

void setOceanTheme(Theme *theme) {
    theme->setColour(ThemeColour::bg, new Colour(55, 63, 81));
    theme->setColour(ThemeColour::bg_two, new Colour(64, 67, 78));
    theme->setColour(ThemeColour::accent, new Colour(0, 141, 213));
    theme->setColour(ThemeColour::accent_two, new Colour(0, 129, 194));
    theme->setColour(ThemeColour::clip, new Colour(255, 23, 68));
    theme->setColour(ThemeColour::warning, new Colour(255, 143, 0));
    theme->setColour(ThemeColour::lcd_bg, new Colour(21, 21, 21));
    theme->setColour(ThemeColour::lcd, new Colour(0, 129, 194));
}


std::string ThemeColourToString(ThemeColour index) {
    switch (index) {
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
        case ThemeColour::warning:
            return "colour_warning";
        case ThemeColour::lcd_bg:
            return "colour_lcd_bg";
        case ThemeColour::lcd:
            return "colour_lcd";
        default:
            return "";
    }
}