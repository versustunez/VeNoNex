#ifndef VENO_PRESETEDITOR_H
#define VENO_PRESETEDITOR_H


#include "../BaseComponent.h"

class PresetEditor : public BaseComponent, public Label::Listener
{
public:
    explicit PresetEditor (const std::string& pid);

    ~PresetEditor () override;

    void resized () override;

    void paint (Graphics& g) override;

    void editorShown (Label* label, TextEditor& editor) override;

    void editorHidden (Label* label, TextEditor& editor) override;

    void labelTextChanged (Label* labelThatHasChanged) override;

protected:
};


#endif //VENO_PRESETEDITOR_H
