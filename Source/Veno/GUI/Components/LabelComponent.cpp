#include "LabelComponent.h"

LabelComponent::LabelComponent (juce::Component* parent, std::string name)
        : m_text (name), m_parent (parent), m_label (std::make_shared<juce::Label> (m_parent->getName (), name))
{
    addAndMakeVisible (*m_label);
}

LabelComponent::~LabelComponent ()
{
    if (m_label != nullptr)
    {
        m_label.reset ();
    }
}

void LabelComponent::resized ()
{
    if (m_label != nullptr)
    {
        m_label->setBounds (0, 0, getWidth (), getHeight ());
    }
}

void LabelComponent::paint (juce::Graphics& g)
{
}

void LabelComponent::setPosition (LabelPosition position)
{
    m_position = position;
}

LabelPosition LabelComponent::getLabelPosition ()
{
    return m_position;
}

void LabelComponent::setListener (juce::Label::Listener* listener)
{
    m_label->addListener (listener);
}

void LabelComponent::setEditable (bool editable)
{
    m_label->setEditable (editable, false, true);
}

void LabelComponent::setJustification (juce::Justification::Flags justification)
{
    m_label->setJustificationType (justification);
}

void LabelComponent::setText (std::string text)
{
    m_label->setText(text, NotificationType::dontSendNotification);
}
