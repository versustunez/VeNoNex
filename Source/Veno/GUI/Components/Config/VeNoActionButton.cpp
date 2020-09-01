#include "VeNoActionButton.h"

#include <utility>
#include "../../../Core/Config.h"
#include "../../../Utils.h"
#include "../../../VenoInstance.h"
#include "../../../Utils/Logger.h"
#include "../../../GUI/Fonts/Fonts.h"
#include "../../../GUI/Fonts/Icons.h"
#include "../../GUIParts/ConfigScreen/VenoConfigScreen.h"
#include "../../GUIParts/Debug/VeNoDebugScreen.h"

VeNoActionButton::VeNoActionButton (const std::string& processId, std::string name, ButtonType type)
        : BaseComponent (processId), m_name (std::move (name)), m_type (type)
{
    setMouseCursor (MouseCursor::PointingHandCursor);
}

void VeNoActionButton::paint (Graphics& g)
{
    auto theme = Config::getInstance ()->getCurrentTheme ();
    VeNo::Utils::setFontSize (16.0f, g);
    g.setColour (theme->getColour (ThemeColour::accent));
    g.drawLine (0, 0, 0, getHeight ());
    g.drawLine (getWidth (), 0, getWidth (), getHeight ());
    auto rect = Rectangle<int> (0, 0, getWidth (), getHeight ());
    switch (m_type)
    {
        case Config:
            VenoFonts::drawIcon (FontAwesome_Cog, g, rect);
            break;
        case Matrix:
            VenoFonts::drawIcon (FontAwesome_Dna, g, rect);
            break;
        case Debug:
            VenoFonts::drawIcon (FontAwesome_Terminal, g, rect);
            break;
        case Presets:
            VenoFonts::drawIcon (FontAwesome_Bars, g, rect);
    }

}

void VeNoActionButton::mouseDown (const MouseEvent& event)
{
    switch (m_type)
    {
        case Config:
            handleConfig();
            break;
        case Matrix:
            handleMatrix();
            break;
        case Debug:
            handleDebug();
            break;
        case Presets:
            handlePresets();
    }

}

void VeNoActionButton::handleConfig ()
{
    auto instance = VenoInstance::getInstance (m_processId);
    if (instance->state->configScreen != nullptr)
    {
        return;
    }
    instance->state->configScreen = new VenoConfigScreen (m_processId);
}

void VeNoActionButton::handleMatrix ()
{

}

void VeNoActionButton::handleDebug ()
{
    auto instance = VenoInstance::getInstance (m_processId);
    if (instance->state->debugScreen != nullptr)
    {
        return;
    }
    instance->state->debugScreen = new VeNoDebugScreen (m_processId);
}

void VeNoActionButton::handlePresets ()
{

}