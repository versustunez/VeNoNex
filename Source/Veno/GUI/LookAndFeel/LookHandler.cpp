#include "LookHandler.h"
#include "../../Core/Config.h"
#include "../../Utils.h"

LookHandler::LookHandler ()
{
}

LookHandler::~LookHandler ()
{
    //delete this shit!
    delete m_feels[0];
    delete m_feels[1];
}

void LookHandler::selectLook (int index)
{
    m_currentLook = index;
}

LookAndFeel_V4* LookHandler::getLook ()
{
    return m_feels[m_currentLook];
}

void LookHandler::drawButtonBackground (Graphics& g, Button& button, const Colour& backgroundColour,
                                        bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown)
{
    getLook ()->drawButtonBackground (g, button, backgroundColour, shouldDrawButtonAsHighlighted,
                                      shouldDrawButtonAsDown);
}

void LookHandler::drawRotarySlider (Graphics& g, int x, int y, int width, int height, float sliderPosProportional,
                                    float rotaryStartAngle, float rotaryEndAngle, Slider& slider)
{
    getLook ()->drawRotarySlider (g, x, y, width, height, sliderPosProportional, rotaryStartAngle, rotaryEndAngle,
                                  slider);
}

void LookHandler::drawTextEditorOutline (Graphics& graphics, int width, int height, TextEditor& editor)
{
    getLook ()->drawTextEditorOutline (graphics, width, height, editor);
}

void LookHandler::drawToggleButton (Graphics& g, ToggleButton& button, bool shouldDrawButtonAsHighlighted,
                                    bool shouldDrawButtonAsDown)
{
    getLook ()->drawToggleButton (g, button, shouldDrawButtonAsHighlighted, shouldDrawButtonAsDown);
}

void LookHandler::drawTabButton (TabBarButton& btn, Graphics& g, bool isMouseOver, bool isMouseDown)
{
    getLook ()->drawTabButton (btn, g, isMouseOver, isMouseDown);
}

void
LookHandler::drawComboBox (Graphics& g, int width, int height, bool isButtonDown, int buttonX, int buttonY, int buttonW,
                           int buttonH, ComboBox& box)
{
    getLook ()->drawComboBox (g, width, height, isButtonDown, buttonX, buttonY, buttonW, buttonH, box);
}

void LookHandler::drawLabel (Graphics& graphics, Label& label)
{
    getLook ()->drawLabel (graphics, label);
}

void LookHandler::drawTabAreaBehindFrontButton (TabbedButtonBar& bar, Graphics& g, int w, int h)
{
    auto theme = Config::getInstance ()->getCurrentTheme ();
    g.setColour (theme->getColour (ThemeColour::bg_two).withAlpha (0.5f));
    g.drawLine (0, h, w, h);
}

PopupMenu::Options LookHandler::getOptionsForComboBoxPopupMenu (ComboBox& box, Label& label)
{
    return PopupMenu::Options ().withTargetComponent (&box)
            .withItemThatMustBeVisible (box.getSelectedId ())
            .withMinimumWidth (box.getWidth ())
            .withMaximumNumColumns (2)
            .withStandardItemHeight (VeNo::Utils::getScaledSize (19));
}


void LookHandler::drawPopupMenuItem (Graphics& g, const Rectangle<int>& area, bool isSeparator, bool isActive,
                                     bool isHighlighted, bool isTicked, bool hasSubMenu, const String& text,
                                     const String& shortcutKeyText, const Drawable* icon, const Colour* textColourToUse)
{
    auto theme = Config::getInstance ()->getCurrentTheme ();
    if (isSeparator)
    {
        auto r = area.reduced (5, 0);
        r.removeFromTop (roundToInt (((float) r.getHeight () * 0.5f) - 0.5f));

        g.setColour (findColour (PopupMenu::textColourId).withAlpha (0.3f));
        g.fillRect (r.removeFromTop (1));
    }
    else
    {
        auto textColour = theme->getColour (ThemeColour::font);
        auto r = area.reduced (1);
        if (isHighlighted && isActive)
        {
            g.setColour (theme->getColour (ThemeColour::accent).withAlpha (0.4f));
            g.fillRect (r);
            g.setColour (theme->getColour (ThemeColour::font));
        }
        else
        {
            g.setColour (textColour.withMultipliedAlpha (isActive ? 1.0f : 0.5f));
        }
        auto font = getPopupMenuFont ();
        auto maxFontHeight = (float) r.getHeight () / 1.3f;
        if (font.getHeight () > maxFontHeight)
            font.setHeight (maxFontHeight);

        g.setFont (font);
        r.removeFromLeft (10);
        g.drawFittedText (text, r, Justification::centredLeft, 1);

        if (isTicked || hasSubMenu)
        {
            g.setColour (theme->getColour (ThemeColour::accent));
            g.fillRect (0, 0, 5, r.getHeight ());
        }
    }
}

void LookHandler::drawPopupMenuBackground (Graphics& g, int width, int height)
{
    auto theme = Config::getInstance ()->getCurrentTheme ();
    g.fillAll (theme->getColour (ThemeColour::bg));
    ignoreUnused (width, height);

#if !JUCE_MAC
    g.setColour (theme->getColour (ThemeColour::bg).withAlpha (0.2f));
    g.drawRect (0, 0, width, height);
#endif
}
