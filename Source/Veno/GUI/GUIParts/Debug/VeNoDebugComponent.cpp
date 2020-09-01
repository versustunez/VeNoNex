#include "VeNoDebugComponent.h"
#include "../../../VenoInstance.h"
#include <utility>

VeNoDebugComponent::VeNoDebugComponent (std::string pid)
        : m_pid (std::move (pid))
{
    setScrollBarsShown (true, false);
    setSize (getWidth (), getHeight ());
    auto parameters = VenoInstance::getInstance (m_pid)->handler->getParameters ();
    auto rawParams = VenoInstance::getInstance (m_pid)->handler->rawParameters ();
    m_knobs.resize (parameters.size ());
    int i = 0;
    for (const auto& parameter : rawParams)
    {
        m_knobs[i] = std::make_unique<VeNoKnob> (parameter, m_pid);
        m_knobs[i]->init (parameters[parameter]->getShowName());
        addAndMakeVisible (*m_knobs[i]);
        i++;
    }

    flexBox.flexDirection = FlexBox::Direction::row;
    flexBox.justifyContent = FlexBox::JustifyContent::flexStart;
    flexBox.flexWrap = FlexBox::Wrap::wrap;
    auto w = 200;
    auto h = 150;
    for (auto& knob : m_knobs)
    {
        auto item = FlexItem (w, h, *knob);
        item.margin = FlexItem::Margin (5, 5, 5, 5);
        flexBox.items.add (item);
    }
}

VeNoDebugComponent::~VeNoDebugComponent ()
{
    for (auto& knob : m_knobs)
    {
        knob.reset ();
    }
}


void VeNoDebugComponent::paint (Graphics& g)
{
    g.fillAll (Config::getInstance ()->getCurrentTheme ()->getColour (ThemeColour::bg));
}

void VeNoDebugComponent::resized ()
{
    auto bounds = Rectangle<int> ();
    bounds.setBounds (0, 0, getWidth (), getHeight ());
    flexBox.performLayout (bounds);
}
