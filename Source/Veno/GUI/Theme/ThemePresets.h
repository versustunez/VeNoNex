#ifndef VENO_THEMEPRESETS_H
#define VENO_THEMEPRESETS_H

#include "Theme.h"

class ThemePresets
{
public:
    static void setLEDTheme (Theme* theme);

    static std::string ThemeColourToString (ThemeColour index);

    static void setOceanTheme (Theme* theme);

    static void setOrangeDreamTheme (Theme* theme);

    static void setBloodTheme (Theme* theme);

    static void setGirlTheme (Theme* theme);
};

#endif //VENO_THEMEPRESETS_H
