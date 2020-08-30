#include "FlatLook.h"
#include "../../GUI/Fonts/Fonts.h"
#include "../../Core/Config.h"
#include "../../Utils.h"


FlatLook::FlatLook ()
{
    setDefaultSansSerifTypeface (VenoFonts::getNormal ()->getTypeface ());
}

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
    auto radius = jmin (width / 2, height / 2) - VeNo::Utils::getCalculatedHeight (3.5f);
    auto centreX = x + width * 0.5f;
    auto centreY = y + height * 0.5f;
    auto angle = rotaryStartAngle + sliderPosProportional * (rotaryEndAngle - rotaryStartAngle);
    float size = VeNo::Utils::getCalculatedHeight (3.5f);

    //---[the real draw]---//
    Path outerArc;
    outerArc.addCentredArc (0, 0, radius, radius, 0, -MAX_RADIAN,
                            MAX_RADIAN,
                            true);
    outerArc.applyTransform (AffineTransform ().translated (centreX, centreY));
    g.setColour (theme->getColour(ThemeColour::accent).withAlpha(0.2f));
    g.strokePath (outerArc, PathStrokeType (size));

    //prepare pointer for drawing
    Path arc;
    arc.addCentredArc (0, 0, radius, radius, 0, -MAX_RADIAN, (sliderPosProportional * 2 - 1) * MAX_RADIAN,
                       true);
    arc.applyTransform (AffineTransform ().translated (centreX, centreY));
    g.setGradientFill (
            ColourGradient::horizontal (theme->getColour (ThemeColour::accent_two), centreX - radius,
                                        theme->getColour (ThemeColour::accent),
                                        centreX + radius));
    g.strokePath (arc, PathStrokeType (size));

    Path pointer;
    auto pointerThickness = VeNo::Utils::getCalculatedHeight (2.5f);
    auto l = VeNo::Utils::getCalculatedHeight (5);
    pointer.addEllipse (-pointerThickness * 0.25f, -(radius - l), pointerThickness, pointerThickness);
    pointer.applyTransform (AffineTransform::rotation (angle).translated (centreX, centreY));
    g.setColour (theme->getColour(ThemeColour::accent));
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
    auto p = VeNo::Utils::getCalculatedHeight (10);
    graphics.drawLine (p, height, width - p, height, 0.9f);
}

void FlatLook::drawToggleButton (Graphics& graphics, ToggleButton& button, bool shouldDrawButtonAsHighlighted,
                                 bool shouldDrawButtonAsDown)
{
    int height = button.getHeight ();
    int width = button.getWidth ();
    auto theme = Config::getInstance ()->getCurrentTheme ();
    std::string text;
    if (shouldDrawButtonAsDown || button.getToggleStateValue () == button.buttonDown)
    {
        graphics.setColour (theme->getColour (ThemeColour::accent));
        text = "On";
    }
    else
    {
        graphics.setColour (theme->getColour (ThemeColour::accent).withAlpha (0.2f));
        text = "Off";
    }

    auto l = VeNo::Utils::getCalculatedHeight (2);
    auto p = VeNo::Utils::getCalculatedHeight (4);
    graphics.fillRect (l, l, width - p, height - p);
    graphics.setColour (theme->getColour (ThemeColour::font));
    graphics.drawText (text, l, l, width - p, height - p, Justification::centred, true);
}

void FlatLook::drawTabButton (TabBarButton& button, Graphics& graphics, bool isMouseOver, bool isMouseDown)
{
    LookAndFeel_V3::drawTabButton (button, graphics, isMouseOver, isMouseDown);
}

void FlatLook::drawComboBox (Graphics& graphics, int width, int height, bool isButtonDown, int buttonX, int buttonY,
                             int buttonW, int buttonH, ComboBox& box)
{
    auto borderHeight = VeNo::Utils::getCalculatedHeight (2);
    auto theme = Config::getInstance ()->getCurrentTheme ();
    graphics.setColour (theme->getColour (ThemeColour::accent));
    graphics.fillRect (0, height - borderHeight, width, borderHeight);
}

void FlatLook::drawLabel (Graphics& graphics, Label& label)
{
    auto theme = Config::getInstance ()->getCurrentTheme ();
    graphics.fillAll (label.findColour (Label::backgroundColourId));
    if (!label.isBeingEdited ())
    {
        auto alpha = label.isEnabled () ? 1.0f : 0.5f;
        const Font font (getLabelFont (label));
        graphics.setColour (theme->getColour (ThemeColour::font).withAlpha (alpha));
        auto textArea = getLabelBorderSize (label).subtractedFrom (label.getLocalBounds ());
        graphics.drawFittedText (label.getText (), textArea, label.getJustificationType (),
                                 jmax (1, (int) ((float) textArea.getHeight () / font.getHeight ())),
                                 label.getMinimumHorizontalScale ());
    }
}
