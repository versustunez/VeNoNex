//
// Created by versustune on 17.03.20.
//

#ifndef VENO_FLATLOOK_H
#define VENO_FLATLOOK_H

#include "JuceHeader.h"

class FlatLook : public LookAndFeel_V4
{
private:
public:
    void drawButtonBackground (Graphics& graphics, Button& button, const Colour& backgroundColour,
                               bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown) override;
protected:
};
#endif //VENO_FLATLOOK_H
