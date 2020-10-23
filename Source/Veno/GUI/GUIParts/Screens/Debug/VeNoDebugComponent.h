#ifndef VENO_DEBUGCOMPONENT_H
#define VENO_DEBUGCOMPONENT_H

#include "JuceHeader.h"
#include "../../../../Core/Config.h"
#include "../../../Components/Base/VeNoKnob.h"

class VeNoDebugComponent : public Viewport
{
public:
    explicit VeNoDebugComponent (std::string pid);

    ~VeNoDebugComponent () override;

    void paint (Graphics& g) override;

    void resized () override;

protected:
    std::string m_pid;
    std::unique_ptr<juce::TextEditor> m_editor;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (VeNoDebugComponent)
};

#endif //VENO_DEBUGCOMPONENT_H
