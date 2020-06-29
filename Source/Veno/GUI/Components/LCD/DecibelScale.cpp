//
// Created by Maurice on 29.06.2020.
//

#include "DecibelScale.h"
#include "../../../Core/Config.h"
#include "../../../Utils.h"
#include "../../../Fonts/Fonts.h"

DecibelScale::DecibelScale (const std::string& process_id) : BaseComponent (process_id)
{

}

void DecibelScale::resized ()
{
    m_scale = 0.95 * getHeight();
}

void DecibelScale::paint (Graphics& g)
{
    VeNo::Utils::setFontSize(7, g);
    auto theme = Config::getInstance ()->getCurrentTheme ();
    g.setColour (theme->getColour (ThemeColour::lcd));
    g.setFont(*VenoFonts::getLCD());
    if (m_mode == 0)
    {
        drawLabel (g, getScale (0), "0");
        drawLabel (g, getScale (-3), "3");
        drawLabel (g, getScale (-6), "6");
        drawLabel (g, getScale (-9), "9");
        drawLabel (g, getScale (-12), "12");
        drawLabel (g, getScale (-18), "18");
        drawLabel (g, getScale (-27), "27");
    }
    else
    {
        g.setOpacity (0);
    }
}

int DecibelScale::getScale (float dB)
{
    float fDef = (dB+30) / 30;
    return int (fDef * m_scale);
}

void DecibelScale::drawLabel (Graphics& g, int y, const std::string& label)
{
    auto font = g.getCurrentFont ();
    int currentY = getHeight () - y;
    int thisWidth = getWidth ();

    int iMidHeight = (int) (font.getHeight () * 0.5f);

    if (font.getStringWidth (label) < thisWidth - 5)
    {
        g.drawLine (0, currentY, 2, currentY);
        g.drawLine (thisWidth - 3, currentY, thisWidth - 1, currentY);
    }

    g.drawText (label,
                2, currentY - iMidHeight, thisWidth - 3, (int) font.getHeight (),
                Justification::centred,
                false);

    m_lastY = currentY + 1;
}
