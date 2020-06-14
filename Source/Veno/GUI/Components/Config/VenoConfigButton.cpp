//
// Created by versustune on 14.06.20.
//

#include "VenoConfigButton.h"
#include "../../../Core/Config.h"
#include "../../../Utils.h"
#include "../../../VenoInstance.h"
#include "../../../Utils/Logger.h"

VenoConfigButton::VenoConfigButton (const std::string& processId) : BaseComponent(processId)
{
    setMouseCursor(MouseCursor::PointingHandCursor);
}

void VenoConfigButton::paint (Graphics& g)
{
    auto theme = Config::getInstance()->getCurrentTheme();
    VeNo::Utils::setFontSize(16.0f, g);
    g.setColour(theme->getColour(ThemeColour::accent));
    g.drawRect(0, 0, getWidth(), getHeight());
    g.drawFittedText("Config", 0, 0, getWidth(), getHeight(), Justification::centred, 1, 1);
}

void VenoConfigButton::mouseDown (const MouseEvent& event)
{
    // open Window on click :)
    auto state = VenoInstance::getInstance(m_processId)->state;
    if (state->configScreen != nullptr)
    {
        return;
    }
    state->configScreen = new VenoConfigScreen(m_processId);
}
