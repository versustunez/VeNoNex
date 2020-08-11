//
// Created by versustune on 13.06.20.
//

#include "Fonts.h"

VenoFonts* VenoFonts::instance = new VenoFonts();

Font* VenoFonts::getNormal ()
{
    return getInstance()->arvo;
}

Font* VenoFonts::getLCD ()
{
    return getInstance()->lcdFont;
}

VenoFonts* VenoFonts::getInstance ()
{
    if (instance == nullptr)
    {
        instance = new VenoFonts();
    }
    return instance;
}

void VenoFonts::destroyAll ()
{
    if (instance != nullptr) {
        delete instance;
    }
    instance = nullptr;
}

VenoFonts::VenoFonts ()
{
    arvo = new Font(Typeface::createSystemTypefaceFor(BinaryData::arvo_ttf,
                                                      BinaryData::arvo_ttfSize));
    lcdFont = new Font(Typeface::createSystemTypefaceFor(BinaryData::lcd_ttf,
                                                         BinaryData::lcd_ttfSize));
}

VenoFonts::~VenoFonts ()
{
    delete arvo;
    delete lcdFont;
    arvo = nullptr;
    lcdFont = nullptr;
}
