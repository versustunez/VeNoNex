//
// Created by versustune on 01.03.20.
//

#include "Theme.h"
#include "ThemePresets.cpp"

Theme::Theme(std::shared_ptr<PropertiesFile> file) {
    m_configFile = file;
}


Theme::~Theme() {
    m_colours.clear();
    m_configFile.reset();
}

void Theme::setColour(ThemeColour index, Colour *colour) {
    auto c = m_colours[index];
    if (c) {
        delete c;
        m_colours[index] = colour;
    } else {
        m_colours[index] = colour;
    }
    m_configFile->setValue(ThemeColourToString(index), colour->toString());
    m_configFile->save();

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
    if (m_configFile->containsKey(key)) {
        auto baseColour = Colour::fromString(m_configFile->getValue(key));
        auto *colour = new Colour(baseColour.getRed(), baseColour.getGreen(), baseColour.getBlue());
        setColour(index, colour);
    }
}
