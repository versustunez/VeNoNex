#include "OscillatorPage.h"

#include <utility>
#include "../../../../Utils.h"
#include "../../../../VenoInstance.h"

namespace VeNo
{

    OscillatorPage::OscillatorPage (std::string name, const std::string& pid)
            : BaseComponent (pid), m_name(std::move(name)), m_helper(std::make_unique<GUIHelper>(m_processId, m_name))
    {
        setupGui();
        for (auto & item : m_helper->m_gui_parts)
        {
            addAndMakeVisible(*item.component);
        }
    }

    void OscillatorPage::resized ()
    {
        for (auto & item : m_helper->m_gui_parts)
        {
            if (item.component != nullptr) {
                item.component->setBounds(Utils::getScaledSize(item.x), Utils::getScaledSize(item.y), Utils::getScaledSize(item.w), Utils::getScaledSize(item.h));
            }
        }
    }

    void OscillatorPage::paint (Graphics& g)
    {
        auto bgColor = Config::getInstance()->getCurrentTheme()->getColour(ThemeColour::bg);
        auto fontColor = Config::getInstance()->getCurrentTheme()->getColour(ThemeColour::font);
        auto fontSize = Utils::setFontSize(13, g);
        for (auto & item : m_helper->m_blocks)
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

    OscillatorPage::~OscillatorPage ()
    {
        m_helper.reset(nullptr);
    }
}