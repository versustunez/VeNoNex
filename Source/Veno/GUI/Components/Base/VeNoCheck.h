#ifndef VENO_VENOCHECK_H
#define VENO_VENOCHECK_H


#include "../BaseComponent.h"
#include "VeNoComponentListener.h"

typedef AudioProcessorValueTreeState::ButtonAttachment ButtonAttachment;

class VeNoCheck : public BaseComponent, public VeNoComponentListener
{
public:
    VeNoCheck (const std::string& name, const std::string& text, const std::string& pid);

    ~VeNoCheck () override;

    void resized () override;

    void paint (Graphics& g) override;

protected:
    std::unique_ptr<ToggleButton> m_button;
    std::unique_ptr<ButtonAttachment> m_attachment;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(VeNoCheck)
};


#endif //VENO_VENOCHECK_H
