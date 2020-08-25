#ifndef VENO_FLATLOOK_H
#define VENO_FLATLOOK_H

#include "JuceHeader.h"

class FlatLook : public LookAndFeel_V4
{
private:
public:
    FlatLook ();

    ~FlatLook () override = default;

    void drawButtonBackground (Graphics& graphics, Button& button, const Colour& backgroundColour,
                               bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown) override;

    void drawRotarySlider (Graphics& graphics, int x, int y, int width, int height, float sliderPosProportional,
                           float rotaryStartAngle, float rotaryEndAngle, Slider& slider) override;

    void drawTextEditorOutline (Graphics& graphics, int width, int height, TextEditor& editor) override;

    void drawToggleButton (Graphics& graphics, ToggleButton& button, bool shouldDrawButtonAsHighlighted,
                           bool shouldDrawButtonAsDown) override;

    void drawTabButton (TabBarButton& button, Graphics& graphics, bool isMouseOver, bool isMouseDown) override;

    void
    drawComboBox (Graphics& graphics, int width, int height, bool isButtonDown, int buttonX, int buttonY, int buttonW,
                  int buttonH, ComboBox& box) override;

protected:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FlatLook);
};

#endif //VENO_FLATLOOK_H
