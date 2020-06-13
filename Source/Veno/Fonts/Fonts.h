//
// Created by versustune on 19.01.20.
//

#ifndef VENO_FONTS_H
#define VENO_FONTS_H

#include "JuceHeader.h"

class VenoFonts
{
protected:
    static VenoFonts* instance;
    Font* lcdFont;
    Font* arvo;
public:
    VenoFonts ();
    ~VenoFonts ();
    static void destroyAll ();
    static Font* getLCD ();
    static Font* getNormal ();
    static VenoFonts* getInstance ();
};
#endif //VENO_FONTS_H
