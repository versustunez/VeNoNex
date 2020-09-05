#include "VeNoColour.h"
#include <utility>
#include "../../../Core/Config.h"
#include "../../../Utils.h"
#include "../../../VenoInstance.h"

using ColourOption = ColourSelector::ColourSelectorOptions;

VeNoColour::~VeNoColour ()
{
    BaseComponent::m_label.reset ();
    m_selector.reset ();
}

VeNoColour::VeNoColour (const std::string& processId, ThemeColour index)
        : BaseComponent (processId),
          m_index (index), m_selector (std::make_unique<ColourSelector> (
                ColourOption::showColourAtTop | ColourOption::editableColour | ColourOption::showColourspace))
{
    m_selector->setCurrentColour (Config::getInstance ()->getCurrentTheme ()->getColour (index),
                                  NotificationType::dontSendNotification);
    m_selector->addChangeListener (this);
    m_selector->setOpaque (false);
    addAndMakeVisible (*m_selector);
}

void VeNoColour::setName (std::string name)
{
    m_name = std::move (name);
    if (BaseComponent::m_label == nullptr)
    {
        BaseComponent::addLabel (m_name, LabelPosition::TOP);
    }
}

void VeNoColour::changeListenerCallback (ChangeBroadcaster* source)
{
    auto selector = m_selector->getCurrentColour ();
    auto* colour = new Colour (selector.getRed (), selector.getGreen (), selector.getBlue (),
                               1.0f);
    Config::getInstance ()->getCurrentTheme ()->setColour (m_index, colour);
    Config::getInstance ()->repaintAll ();
    if (VenoInstance::getInstance (m_processId)->state->configScreen != nullptr)
    {
        VenoInstance::getInstance (m_processId)->state->configScreen->repaint ();
    }
}

void VeNoColour::resized ()
{
    auto h = VeNo::Utils::getScaledSize (30);
    if (BaseComponent::m_label != nullptr)
    {
        BaseComponent::m_label->setBounds (0, 0, getWidth (), h);
    }
    if (m_selector != nullptr)
    {
        m_selector->setBounds (0, h, getWidth (), getHeight () - h);
    }
}

void VeNoColour::paint (Graphics& g)
{
    m_selector->setCurrentColour (Config::getInstance ()->getCurrentTheme ()->getColour (m_index),
                                  NotificationType::dontSendNotification);
    g.setColour (Colours::white);
    BaseComponent::paint (g);
}
