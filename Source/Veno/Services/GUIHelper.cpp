#include "GUIHelper.h"

#include <utility>
#include "../VenoInstance.h"
#include "../GUI/Components/Base/VeNoCheck.h"
#include "../GUI/Components/Base/VeNoTextButton.h"
#include "../Utils.h"

namespace VeNo
{

    void GUIHelper::createItem (GUIItem item)
    {
        // search parameter
        auto param = VenoInstance::getInstance (m_pid)->handler->getParameter (item.parameter);
        if (param != nullptr)
        {
            if (item.type == "slider")
            {
                auto knob = new VeNoKnob (item.parameter, m_pid);
                knob->init (item.name);
                item.component = knob;
            }
            else if (item.type == "box")
            {
                auto select = new VeNoSelect (item.parameter, m_pid);
                select->init (item.name, LabelPosition::BOTTOM, item.selectType);
                select->select (param->getAsInt ());
                item.component = select;
            }
            else if (item.type == "checkbox")
            {
                auto checkbox = new VeNoCheck (item.parameter, item.name, m_pid);
                item.component = checkbox;
            }
            else
            {
                return;
            }
        }
        else
        {
            if (item.type == "textButton")
            {
                auto textButton = new VeNoTextButton (item.parameter, item.name, m_pid);
                textButton->setToCall(item.parameter, m_name);
                item.component = textButton;
            }
            else
            {
                return;
            }
        }
        m_gui_parts.push_back (item);
    }

    GUIHelper::GUIHelper (std::string pid, std::string name)
            : m_pid (std::move (pid)), m_name (std::move(name))
    {
    }

    GUIHelper::~GUIHelper ()
    {
        for (auto& item : m_gui_parts)
        {
            delete item.component;
        }
    }

    void GUIHelper::drawBlocks (Graphics& g)
    {
        auto theme = Config::getInstance ()->getCurrentTheme ();
        auto bgColor = theme->getColour (ThemeColour::bg);
        auto fontColor = theme->getColour (ThemeColour::font);
        auto fontSize = Utils::setFontSize (13, g);
        for (auto& item : m_blocks)
        {
            int x = Utils::getScaledSize (item.x);
            int y = Utils::getScaledSize (item.y);
            int w = Utils::getScaledSize (item.w);
            int h = Utils::getScaledSize (item.h);
            g.setColour (bgColor);
            g.fillRoundedRectangle (x, y, w, h, Utils::getScaledSize (8));
            g.setColour (fontColor);
            g.drawText (item.name, x, y, w, fontSize, Justification::centred);
        }
    }

    void GUIHelper::resizeComponents ()
    {
        for (auto& item : m_gui_parts)
        {
            if (item.component != nullptr)
            {
                item.component->setBounds (
                        Utils::getScaledSize (item.x),
                        Utils::getScaledSize (item.y),
                        Utils::getScaledSize (item.w),
                        Utils::getScaledSize (item.h)
                );
            }
        }
    }

    void GUIHelper::makeVisible (GUICreator* component)
    {
        component->setupGui();
        for (auto& item : m_gui_parts)
        {
            component->addAndMakeVisible (*item.component);
        }
    }
}