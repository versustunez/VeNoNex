//
// Created by versustune on 19.01.20.
//

#ifndef VENO_FONTS_H
#define VENO_FONTS_H

#include "JuceHeader.h"

class VenoFonts {
public:
    static const Font &getLCD() {
        static Font lcd(Font(Typeface::createSystemTypefaceFor(BinaryData::lcd_ttf,
                                                               BinaryData::lcd_ttfSize)));
        return lcd;
    }

    static const Font &getNormal() {
        static Font arvo(Font(Typeface::createSystemTypefaceFor(BinaryData::arvo_ttf,
                                                                BinaryData::arvo_ttfSize)));
        return arvo;
    }
};

#endif //VENO_FONTS_H
