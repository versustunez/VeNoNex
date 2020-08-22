#ifndef VENO_FONTS_H
#define VENO_FONTS_H

#include "JuceHeader.h"

class VenoFonts
{
protected:
    static VenoFonts* instance;
    Font* lcdFont;
    Font* arvo;
    Font* icons;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (VenoFonts)
public:
    VenoFonts ();
    ~VenoFonts ();
    static void destroyAll ();
    static Font* getLCD ();
    static Font* getNormal ();
    static VenoFonts* getInstance ();
    static Font* getIcons() ;
    static void drawIcon(const String& icon, Graphics& g, Rectangle<int>& space);
};
#endif //VENO_FONTS_H
