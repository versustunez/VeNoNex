#include "PresetEditor.h"
#include "../../../VenoInstance.h"
#include "../../../Utils.h"


PresetEditor::PresetEditor (const std::string& pid) : BaseComponent (pid)
{
    auto instance = VenoInstance::getInstance (m_processId);
    instance->changeListener->addListener("presetEditor", this);
    addLabel (instance->presetManager->m_name, LabelPosition::NO_LABEL);
    m_label->setListener (this);
    m_label->setEditable (true);
    m_label->setJustification (Justification::centred);
}

PresetEditor::~PresetEditor ()
{
    if (m_label != nullptr)
    {
        m_label.reset ();
    }
    auto instance = VenoInstance::getInstance (m_processId);
    instance->changeListener->removeListener("presetEditor");
}

void PresetEditor::resized ()
{
    if (m_label != nullptr)
    {
        m_label->setBounds (0, 0, getWidth (), getHeight ());
    }
}

void PresetEditor::paint (Graphics& g)
{
    auto h = VeNo::Utils::getScaledSize (1);
    auto theme = Config::getInstance ()->getCurrentTheme ();
    g.setColour (theme->getColour (ThemeColour::bg_two).withAlpha (0.4f));
    g.fillAll ();
    g.setColour (theme->getColour (ThemeColour::accent));
    g.fillRect (0, getHeight () - h, getWidth (), h);
}

void PresetEditor::editorShown (Label* label, TextEditor& editor)
{
    editor.setJustification (Justification::centred);
    editor.setText (label->getText (false));
}

void PresetEditor::editorHidden (Label* label, TextEditor& editor)
{
    VenoInstance::getInstance (m_processId)->presetManager->setName (editor.getText ().toStdString ());
    label->setText (editor.getText (), NotificationType::dontSendNotification);
}

void PresetEditor::labelTextChanged (Label* labelThatHasChanged)
{

}

void PresetEditor::parameterChanged (VeNoParameter* parameter)
{

}

void PresetEditor::notify (const std::string& name, double value)
{
    m_label->setText (VenoInstance::getInstance (m_processId)->presetManager->m_name);
}
