#include "VeNoDebugComponent.h"
#include "../../../../VenoInstance.h"
#include <utility>

VeNoDebugComponent::VeNoDebugComponent (std::string pid)
        : m_pid (std::move (pid))
{
    setScrollBarsShown (true, false);
    setSize (getWidth (), getHeight ());
    auto instance = VenoInstance::getInstance (m_pid);
    auto state = instance->presetManager->getCurrentData();
    m_editor = std::make_unique<juce::TextEditor> ();
    m_editor->setMultiLine (true);
    m_editor->setText (state->toString ());
    m_editor->setScrollbarsShown (true);
    addAndMakeVisible (*m_editor);
}

VeNoDebugComponent::~VeNoDebugComponent ()
{
    m_editor.reset ();
}


void VeNoDebugComponent::paint (Graphics& g)
{
    g.fillAll (Config::getInstance ()->getCurrentTheme ()->getColour (ThemeColour::bg));
}

void VeNoDebugComponent::resized ()
{
    m_editor->setBounds (0, 0, getWidth (), getHeight ());
}
