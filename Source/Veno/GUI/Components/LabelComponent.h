#ifndef VENO_LABELCOMPONENT_H
#define VENO_LABELCOMPONENT_H

#include "JuceHeader.h"

enum LabelPosition
{
    NO_LABEL,
    TOP,
    BOTTOM
};

class LabelComponent : public juce::Component
{
public:
    LabelComponent (juce::Component* parent, std::string name);

    ~LabelComponent () override;

    void resized () override;

    void paint (juce::Graphics& g) override;

    void setPosition (LabelPosition position);

    void setListener (juce::Label::Listener* listener);

    void setEditable (bool editable);

    void setJustification (juce::Justification::Flags justification);

    LabelPosition getLabelPosition ();

protected:
private:
    std::string m_text;
    juce::Component* m_parent;
    LabelPosition m_position = LabelPosition::NO_LABEL;
    std::shared_ptr<juce::Label> m_label;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LabelComponent)
};

#endif //VENO_LABELCOMPONENT_H
