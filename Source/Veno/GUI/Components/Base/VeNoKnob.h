#ifndef VENO_VENOKNOB_H
#define VENO_VENOKNOB_H

#include "JuceHeader.h"
#include "../BaseComponent.h"
#include "VeNoComponentListener.h"

typedef AudioProcessorValueTreeState::SliderAttachment SliderAttachment;

class VeNoKnob : public BaseComponent, public Label::Listener, public VeNoComponentListener
{
public:
    VeNoKnob (const std::string& name, const std::string& pid);

    ~VeNoKnob () override;

    void init (const std::string& label);

    void resized () override;

    void editorShown (Label* label, TextEditor& editor) override;

    void editorHidden (Label* label, TextEditor& editor) override;

    void labelTextChanged (Label* labelThatHasChanged) override;

    std::unique_ptr<Slider> m_slider;
protected:
    std::string m_labelText = "";
    std::string m_name;
    std::unique_ptr<SliderAttachment> m_attachment;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(VeNoKnob)
};


#endif //VENO_VENOKNOB_H
