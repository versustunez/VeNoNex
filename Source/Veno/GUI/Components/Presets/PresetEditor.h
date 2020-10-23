#ifndef VENO_PRESETEDITOR_H
#define VENO_PRESETEDITOR_H


#include "../BaseComponent.h"
#include "../../../Core/VeNoListener.h"

class PresetEditor : public BaseComponent, public Label::Listener, public VeNoListener
{
public:
    explicit PresetEditor (const std::string& pid);

    ~PresetEditor () override;

    void resized () override;

    void paint (Graphics& g) override;

    void editorShown (Label* label, TextEditor& editor) override;

    void editorHidden (Label* label, TextEditor& editor) override;

    void labelTextChanged (Label* labelThatHasChanged) override;

    void parameterChanged (VeNoParameter* parameter) override;

    void notify (const std::string& name, double value) override;

protected:
};


#endif //VENO_PRESETEDITOR_H
