#include "VenoConfigButton.h"
#include "../../../Core/Config.h"
#include "../../../Utils.h"
#include "../../../VenoInstance.h"
#include "../../../Utils/Logger.h"
#include "../../../GUI/Fonts/Fonts.h"
#include "../../../GUI/Fonts/Icons.h"

VenoConfigButton::VenoConfigButton (const std::string& processId) : BaseComponent (processId)
{
    setMouseCursor (MouseCursor::PointingHandCursor);
}

void VenoConfigButton::paint (Graphics& g)
{
    auto theme = Config::getInstance ()->getCurrentTheme ();
    VeNo::Utils::setFontSize (16.0f, g);
    g.setColour (theme->getColour (ThemeColour::accent));
    g.drawLine (0, 0, 0, getHeight ());
    g.drawLine (getWidth (), 0, getWidth (), getHeight ());
    auto rect = Rectangle<int> (0, 0, getWidth (), getHeight ());
    VenoFonts::drawIcon (FontAwesome_Cog, g, rect);
}

void VenoConfigButton::mouseDown (const MouseEvent& event)
{
    // open Window on click :)
    auto instance = VenoInstance::getInstance (m_processId);
    if (instance->state->configScreen != nullptr)
    {
        return;
    }
    instance->state->configScreen = new VenoConfigScreen (m_processId);
}
