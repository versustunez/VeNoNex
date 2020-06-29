//
// Created by versustune on 17.03.20.
//

#include "FlatLook.h"
#include "../../Core/Config.h"

void FlatLook::drawButtonBackground (Graphics& graphics, Button& button, const Colour& backgroundColour,
                                     bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown)
{
    auto theme = Config::getInstance ()->getCurrentTheme ();
    auto buttonArea = button.getLocalBounds ();
    if (shouldDrawButtonAsHighlighted)
    {
        graphics.setColour (theme->getColour (ThemeColour::accent));
    }
    else
    {
        graphics.setColour (theme->getColour (ThemeColour::accent_two));
    }
    graphics.drawRect (buttonArea);
}

void FlatLook::drawRotarySlider (Graphics& g, int x, int y, int width, int height, float sliderPosProportional,
                                 float rotaryStartAngle, float rotaryEndAngle, Slider& slider)
{
    auto theme = Config::getInstance ()->getCurrentTheme ();
    float MAX_RADIAN = 2.53073;
    auto radius = jmin (width / 2, height / 2) - 4.0f;
    auto centreX = x + width * 0.5f;
    auto centreY = y + height * 0.5f;
    auto angle = rotaryStartAngle + sliderPosProportional * (rotaryEndAngle - rotaryStartAngle);

    //---[the real draw]---//
    Path outerArc;
    outerArc.addCentredArc (0, 0, radius, radius, 0, -MAX_RADIAN,
                            MAX_RADIAN,
                            true);
    outerArc.applyTransform (AffineTransform ().translated (centreX, centreY));
    g.setColour (Colour (65, 65, 65));
    g.strokePath (outerArc, PathStrokeType (3.0f));

    //prepare pointer for drawing
    Path arc;
    arc.addCentredArc (0, 0, radius, radius, 0, -MAX_RADIAN, (sliderPosProportional * 2 - 1) * MAX_RADIAN,
                       true);
    arc.applyTransform (AffineTransform ().translated (centreX, centreY));
    g.setGradientFill (
            ColourGradient::horizontal (theme->getColour (ThemeColour::accent_two), centreX - radius,theme->getColour (ThemeColour::accent),
                                        centreX + radius));
    g.strokePath (arc, PathStrokeType (3.0f));

    Path pointer;
    auto pointerThickness = 3;
    pointer.addEllipse (-pointerThickness * 0.25f, -(radius - 5), pointerThickness, pointerThickness);
    pointer.applyTransform (AffineTransform::rotation (angle).translated (centreX, centreY));
    g.setColour (Colour (125, 125, 125));
    g.fillPath (pointer);
}

void FlatLook::drawTextEditorOutline (Graphics& graphics, int width, int height, TextEditor& editor)
{
    auto theme = Config::getInstance ()->getCurrentTheme ();
    graphics.setGradientFill (
            ColourGradient::horizontal (
                    theme->getColour (ThemeColour::accent_two),
                    0,
                    theme->getColour (ThemeColour::accent),
                    width
            )
    );
    graphics.drawLine (10, height, width - 10, height, 0.9f);
}

void FlatLook::drawToggleButton (Graphics& graphics, ToggleButton& button, bool shouldDrawButtonAsHighlighted,
                                 bool shouldDrawButtonAsDown)
{
    LookAndFeel_V4::drawToggleButton (graphics, button, shouldDrawButtonAsHighlighted, shouldDrawButtonAsDown);
}

void FlatLook::drawTabButton (TabBarButton& button, Graphics& graphics, bool isMouseOver, bool isMouseDown)
{
    LookAndFeel_V3::drawTabButton (button, graphics, isMouseOver, isMouseDown);
}

void FlatLook::drawComboBox (Graphics& graphics, int width, int height, bool isButtonDown, int buttonX, int buttonY,
                             int buttonW, int buttonH, ComboBox& box)
{
    auto theme = Config::getInstance ()->getCurrentTheme ();
    graphics.setColour (theme->getColour (ThemeColour::bg));
    graphics.fillRect (0, 0, width, height);
    graphics.setColour (theme->getColour (ThemeColour::accent));
    graphics.drawRect (0, 0, width, height);
}
