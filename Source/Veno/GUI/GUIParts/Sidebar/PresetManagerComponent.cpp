#include "PresetManagerComponent.h"
#include "../../../Utils.h"

PresetManagerComponent::PresetManagerComponent (const std::string& pid) : BaseComponent (pid),
                                                                          m_editor (
                                                                                  std::make_unique<PresetEditor> (pid))
{
    m_prev = std::make_unique<PresetAction> (pid, "prev", PresetAction::Type::PREV);
    m_next = std::make_unique<PresetAction> (pid, "next", PresetAction::Type::NEXT);
    m_save = std::make_unique<PresetAction> (pid, "save", PresetAction::Type::SAVE);
    addAndMakeVisible (*m_prev);
    addAndMakeVisible (*m_next);
    addAndMakeVisible (*m_save);
    addAndMakeVisible (*m_editor);
}


void PresetManagerComponent::resized ()
{
    auto iconWidth = VeNo::Utils::getCalculatedWidth (30);
    auto editorWidth = getWidth () - (iconWidth * 3);
    m_editor->setBounds (0, 0, editorWidth, getHeight ());
    m_save->setBounds (editorWidth, 0, iconWidth, getHeight ());
    m_prev->setBounds (editorWidth + iconWidth, 0, iconWidth, getHeight ());
    m_next->setBounds (editorWidth + (iconWidth * 2), 0, iconWidth, getHeight ());
}

void PresetManagerComponent::paint (Graphics& g)
{
}