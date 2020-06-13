//
// Created by versustune on 17.03.20.
//

#include "BaseComponent.h"
#include "../../Fonts/Fonts.h"
#include <utility>

BaseComponent::BaseComponent (const std::string& processId)
{
    m_processId = processId;
}

BaseComponent::~BaseComponent ()
{
    m_label.reset ();
}

void BaseComponent::addLabel (const std::string& label_text, LabelPosition labelPosition)
{
    m_enableLabel = true;
    m_label = std::make_shared<LabelComponent> (this, label_text);
    m_label->setPosition (labelPosition);
}

void BaseComponent::resized ()
{
    if (m_enableLabel && m_label != nullptr)
    {
        LabelPosition position = m_label->getLabelPosition ();
        if (position == LabelPosition::TOP)
        {
            m_label->setBounds (0, 0, getWidth (), 15);
        }
        else if (position == LabelPosition::BOTTOM)
        {
            m_label->setBounds (0, getHeight () - 20, getWidth (), 15);
        }
    }
}

void BaseComponent::paint (Graphics& g)
{
    g.setFont (*VenoFonts::getNormal ());
}

void BaseComponent::setParameter (std::string name, std::string group)
{
    m_name = std::move (name);
    m_group = std::move (group);
    setName (m_name);
}
