#include "BaseComponent.h"
#include "../../Utils.h"
#include "../../GUI/Fonts/Fonts.h"
#include <utility>

BaseComponent::BaseComponent (const std::string& processId)
        : m_processId (processId)
{
}

BaseComponent::~BaseComponent ()
{
    if (m_enableLabel)
    {
        m_label.reset ();
    }
}

void BaseComponent::addLabel (const std::string& label_text, LabelPosition labelPosition)
{
    m_enableLabel = true;
    m_label = std::make_shared<LabelComponent> (this, label_text);
    m_label->setPosition (labelPosition);
    addAndMakeVisible (*m_label);
}

void BaseComponent::resized ()
{
    if (m_enableLabel && m_label != nullptr)
    {
        LabelPosition position = m_label->getLabelPosition ();
        if (position == LabelPosition::TOP)
        {
            m_label->setBounds (0, 0, getWidth (), VeNo::Utils::getScaledSize (16));
        }
        else if (position == LabelPosition::BOTTOM)
        {
            auto height = VeNo::Utils::getScaledSize (16);
            m_label->setBounds (0, getHeight () - height, getWidth (), height);
        }
    }
}

void BaseComponent::paint (Graphics& g)
{
    g.setFont (*VenoFonts::getNormal ());
    VeNo::Utils::setFontSize(16,g);
}

void BaseComponent::setParameter (std::string name)
{
    m_name = std::move (name);
    setName (m_name);
}
