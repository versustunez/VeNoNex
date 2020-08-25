#include "Fonts.h"
#include "../../Utils.h"

VenoFonts* VenoFonts::instance = new VenoFonts();

Font* VenoFonts::getNormal()
{
    return getInstance()->arvo;
}

Font* VenoFonts::getLCD()
{
    return getInstance()->lcdFont;
}

Font* VenoFonts::getIcons()
{
    return getInstance()->icons;
}

VenoFonts* VenoFonts::getInstance()
{
    if (instance == nullptr)
    {
        instance = new VenoFonts();
    }
    return instance;
}

void VenoFonts::destroyAll()
{
    delete instance;
    instance = nullptr;
}

VenoFonts::VenoFonts()
{
    arvo = new Font(Typeface::createSystemTypefaceFor(BinaryData::arvo_ttf,
                                                      BinaryData::arvo_ttfSize));
    lcdFont = new Font(Typeface::createSystemTypefaceFor(BinaryData::lcd_ttf,
                                                         BinaryData::lcd_ttfSize));
    icons = new Font(Typeface::createSystemTypefaceFor(BinaryData::fontAwesome_ttf,
                                                       BinaryData::fontAwesome_ttfSize));
}

VenoFonts::~VenoFonts()
{
    delete arvo;
    delete lcdFont;
    delete icons;
    arvo = nullptr;
    lcdFont = nullptr;
    icons = nullptr;
}

void VenoFonts::drawIcon(const String& icon, Graphics& g, Rectangle<int>& space)
{
    auto font = g.getCurrentFont();
    g.setFont(*VenoFonts::getIcons());
    g.drawText(icon, space, Justification::centred, true);
    g.setFont(font);
}
