//
// Created by versustune on 07.06.20.
//

#include "LabelComponent.h"

LabelComponent::LabelComponent(Component *parent, std::string name) {
    m_text = name;
    m_parent = parent;
    m_label = std::make_shared<Label>(m_parent->getName(), name);
}

LabelComponent::~LabelComponent() {
    m_label.reset();
}

void LabelComponent::resized() {
    if (m_label != nullptr) {
        m_label->setBounds(0, 0, getWidth(), getHeight());
    }
}

void LabelComponent::paint(Graphics &g) {
}

void LabelComponent::setPosition(LabelPosition position) {
    m_position = position;
}

LabelPosition LabelComponent::getLabelPosition() {
    return m_position;
}
