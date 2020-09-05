#include "VeNoCheck.h"
#include "../../../VenoInstance.h"

VeNoCheck::VeNoCheck (const std::string& name, const std::string& text, const std::string& pid)
        : BaseComponent (pid), VeNoComponentListener (pid), m_button(std::make_unique<ToggleButton> (text))
{
    m_button->setComponentID (name);
    auto treeState = VenoInstance::getInstance (m_processId)->treeState;
    m_attachment = std::make_unique<ButtonAttachment> (*treeState, name, *m_button);
    addAndMakeVisible (*m_button);
}

VeNoCheck::~VeNoCheck ()
{
    m_attachment.reset ();
    m_button.reset ();
}

void VeNoCheck::resized ()
{
    m_button->setBounds (0, 0, getWidth (), getHeight ());
}

void VeNoCheck::paint (Graphics& g)
{
    BaseComponent::paint (g);
}
