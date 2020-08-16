//
// Created by versustune on 07.06.20.
//

#ifndef VENO_LABELCOMPONENT_H
#define VENO_LABELCOMPONENT_H

#include "JuceHeader.h"

enum LabelPosition
{
    NO_LABEL,
    TOP,
    BOTTOM
};
class LabelComponent : public Component
{
public:
    LabelComponent (Component* parent, std::string name);
    ~LabelComponent () override;
    void resized () override;
    void paint (Graphics& g) override;
    void setPosition (LabelPosition position);
    LabelPosition getLabelPosition ();
protected:
private:
    std::string m_text;
    Component* m_parent;
    LabelPosition m_position = LabelPosition::NO_LABEL;
    std::shared_ptr<Label> m_label;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LabelComponent)
};
#endif //VENO_LABELCOMPONENT_H
