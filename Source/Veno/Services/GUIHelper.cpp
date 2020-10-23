#include "GUIHelper.h"

#include <utility>
#include "../VenoInstance.h"
#include "../GUI/Components/Base/VeNoCheck.h"
#include "../GUI/Components/Base/VeNoTextButton.h"

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
        for (auto & item : m_gui_parts)
        {
            delete item.component;
        }
    }
}