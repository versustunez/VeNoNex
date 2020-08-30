#include "PresetAction.h"
#include "../../Fonts/Fonts.h"
#include "../../Theme/Theme.h"
#include "../../../Utils.h"
#include "../../../Core/Config.h"
#include "../../Fonts/Icons.h"

#include <utility>

PresetAction::PresetAction (const std::string& processId, std::string name, PresetAction::Type type)
        : BaseComponent (processId), m_name (std::move (name)), m_type (type)
{
    setMouseCursor (MouseCursor::PointingHandCursor);
}

void PresetAction::resized ()
{

}

void PresetAction::paint (Graphics& g)
{
    auto theme = Config::getInstance ()->getCurrentTheme ();
    VeNo::Utils::setFontSize (16.0f, g);
    g.setColour (theme->getColour (ThemeColour::accent));
    auto rect = Rectangle<int> (0, 0, getWidth (), getHeight ());
    g.drawRect (rect, 1);
    switch (m_type)
    {
        case PREV:
            VenoFonts::drawIcon (FontAwesome_AngleLeft, g, rect);
            break;
        case NEXT:
            VenoFonts::drawIcon (FontAwesome_AngleRight, g, rect);
            break;
        case SAVE:
            VenoFonts::drawIcon (FontAwesome_Save, g, rect);
            break;
    }
}

PresetAction::~PresetAction ()
{

}
