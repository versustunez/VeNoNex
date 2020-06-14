//
// Created by versustune on 17.03.20.
//

#include "FlatLook.h"
#include "../../Core/Config.h"

void FlatLook::drawButtonBackground (Graphics& graphics, Button& button, const Colour& backgroundColour,
                                     bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown)
{
    auto theme = Config::getInstance()->getCurrentTheme();
    auto buttonArea = button.getLocalBounds();
    if (shouldDrawButtonAsHighlighted)
    {
        graphics.setColour(theme->getColour(ThemeColour::accent));
    }
    else
    {
        graphics.setColour(theme->getColour(ThemeColour::accent_two));
    }
    graphics.drawRect(buttonArea);
}
