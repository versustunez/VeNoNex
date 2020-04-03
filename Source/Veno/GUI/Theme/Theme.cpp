//
// Created by versustune on 01.03.20.
//

#include "Theme.h"
#include "ThemePresets.cpp"

Theme::Theme(std::shared_ptr<PropertiesFile> file) {
    configFile = file;
}


Theme::~Theme() {
    colours.clear();
    configFile.reset();
}

void Theme::setColour(ThemeColour index, Colour *colour) {
    auto c = colours[index];
    if (c) {
        delete c;
        colours[index] = colour;
    } else {
        colours[index] = colour;
    }
    configFile->setValue(ThemeColourToString(index), colour->toString());
    configFile->save();

}

void Theme::init() {
    setLEDTheme(this);
    getColourFromConfig(ThemeColour::bg);
    getColourFromConfig(ThemeColour::bg_two);
    getColourFromConfig(ThemeColour::accent);
    getColourFromConfig(ThemeColour::accent_two);
    getColourFromConfig(ThemeColour::warning);
    getColourFromConfig(ThemeColour::clip);
    getColourFromConfig(ThemeColour::lcd_bg);
    getColourFromConfig(ThemeColour::lcd);
}

void Theme::getColourFromConfig(ThemeColour index) {
    std::string key = ThemeColourToString(index);
    if (configFile->containsKey(key)) {
        auto baseColour = Colour::fromString(configFile->getValue(key));
        auto *colour = new Colour(baseColour.getRed(), baseColour.getGreen(), baseColour.getBlue());
        setColour(index, colour);
    }
}
