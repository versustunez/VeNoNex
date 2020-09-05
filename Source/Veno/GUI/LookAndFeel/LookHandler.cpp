#include "LookHandler.h"
#include "../../Core/Config.h"

LookHandler::LookHandler ()
{
    selectLook (Config::getInstance ()->getCurrentLook ());
}

LookHandler::~LookHandler ()
{
    //delete this shit!
    delete m_feels[0];
    delete m_feels[1];
    m_look.reset ();
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