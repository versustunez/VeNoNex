#include "OscillatorPage.h"
#include "../../../Utils.h"
#include "../../../VenoInstance.h"
#include "../Base/VeNoCheck.h"

namespace VeNo
{

    OscillatorPage::OscillatorPage (const std::string& name, const std::string& pid)
            : BaseComponent (pid), m_name(name)
    {
        setupGui();
    }

    void OscillatorPage::resized ()
    {
        for (auto & item : m_gui_parts)
        {
            if(item.component != nullptr) {
                item.component->setBounds(Utils::getScaledSize(item.x), Utils::getScaledSize(item.y), Utils::getScaledSize(item.w), Utils::getScaledSize(item.h));
            }
        }
    }

    void OscillatorPage::paint (Graphics& g)
    {
        auto bgColor = Config::getInstance()->getCurrentTheme()->getColour(ThemeColour::bg);
        auto fontColor = Config::getInstance()->getCurrentTheme()->getColour(ThemeColour::font);
        auto fontSize = Utils::setFontSize(13, g);
        for (auto & item : m_blocks)
        {
            int x = Utils::getScaledSize(item.x);
            int y = Utils::getScaledSize(item.y);
            int w = Utils::getScaledSize(item.w);
            int h = Utils::getScaledSize(item.h);
            g.setColour(bgColor);
            g.fillRoundedRectangle(x,y,w,h, Utils::getScaledSize(10));
            g.setColour(fontColor);
            g.drawText(item.name, x, y, w, fontSize, Justification::centred);
        }
    }

    void OscillatorPage::createItem (GUIItem item)
    {
        // search parameter
        auto param = VenoInstance::getInstance (m_processId)->handler->getParameter (item.parameter);
        if (param != nullptr)
        {
            if (item.type == "slider")
            {
                auto knob = new VeNoKnob (item.parameter, m_processId);
                knob->init (item.name);
                addAndMakeVisible (*knob);
                item.component = knob;
            }
            else if (item.type == "box")
            {
                auto select = new VeNoSelect (item.parameter, m_processId);
                select->init (item.name, LabelPosition::BOTTOM, item.selectType);
                select->select(param->getAsInt());
                addAndMakeVisible (*select);
                item.component = select;
            }
            else if (item.type == "checkbox")
            {
                auto checkbox = new VeNoCheck(item.parameter, item.name, m_processId);
                addAndMakeVisible(*checkbox);
                item.component = checkbox;
            }
            else {
                return;
            }
            m_gui_parts.push_back(item);
        }
    }

    OscillatorPage::~OscillatorPage ()
    {
        for (auto & m_gui_part : m_gui_parts)
        {
            delete m_gui_part.component;
        }
        m_gui_parts.clear ();
    }
}