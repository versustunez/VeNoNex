//
// Created by versustune on 01.03.20.
//

#ifndef VENO_THEME_H
#define VENO_THEME_H

#include "JuceHeader.h"
#include <vector>

enum class ThemeColour {
    bg = 0, bg_two, accent, accent_two, warning, clip, lcd_bg, lcd
};

class Theme {
private:
public:
    explicit Theme(std::shared_ptr<PropertiesFile> file);
    ~Theme();

    void setColour(ThemeColour index, Colour *colour);
    void setColourThemeById(int id);
    void init();
    void getColourFromConfig(ThemeColour index);
    Colour getColour(ThemeColour index);
protected:
    std::map<ThemeColour, Colour*> m_colours;
    std::shared_ptr<PropertiesFile> m_configFile;
};


#endif //VENO_THEME_H
