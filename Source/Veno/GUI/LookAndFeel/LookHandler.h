#ifndef VENO_LOOKHANDLER_H
#define VENO_LOOKHANDLER_H

#include "JuceHeader.h"
#include "CrazyLook.h"
#include "FlatLook.h"
#include <memory>

/**
 * overwrite the basic m_look and feel based on the selected Look and Feel :)
 */
class LookHandler : public LookAndFeel_V4
{
private:
    int m_currentLook = 0;
public:
    LookHandler ();

    ~LookHandler () override;

    void selectLook (int index);

    LookAndFeel_V4* getLook ();

    void drawButtonBackground (Graphics& g, Button& button, const Colour& backgroundColour,
                               bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown) override;

    void drawRotarySlider (Graphics& g, int x, int y, int width, int height, float sliderPosProportional,
                           float rotaryStartAngle, float rotaryEndAngle, Slider& slider) override;

    void drawTextEditorOutline (Graphics& graphics, int width, int height, TextEditor& editor) override;

    void drawToggleButton (Graphics& g, ToggleButton& button, bool shouldDrawButtonAsHighlighted,
                           bool shouldDrawButtonAsDown) override;

    void drawTabButton (TabBarButton& btn, Graphics& g, bool isMouseOver, bool isMouseDown) override;

    void
    drawComboBox (Graphics& g, int width, int height, bool isButtonDown, int buttonX, int buttonY, int buttonW,
                  int buttonH, ComboBox& box) override;

    void drawLabel (Graphics& graphics, Label& label) override;

    void drawTabAreaBehindFrontButton (TabbedButtonBar& bar, Graphics& g, int w, int h) override;

    void drawPopupMenuItem (Graphics& graphics, const Rectangle<int>& area, bool isSeparator, bool isActive,
                            bool isHighlighted, bool isTicked, bool hasSubMenu, const String& text,
                            const String& shortcutKeyText, const Drawable* icon, const Colour* textColour) override;

    PopupMenu::Options getOptionsForComboBoxPopupMenu (ComboBox& box, Label& label) override;

    void drawPopupMenuBackground (Graphics& graphics, int width, int height) override;

protected:
    //currently both available themes are CrazyLook <-- (this is a fun one xD) and FlatLook
    LookAndFeel_V4* m_feels[2] = {new FlatLook (), new CrazyLook ()};
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LookHandler);
};

#endif //VENO_LOOKHANDLER_H
