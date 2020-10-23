#ifndef VENO_VENODEBUGSCREEN_H
#define VENO_VENODEBUGSCREEN_H

#include "JuceHeader.h"
#include "../../../../Core/Config.h"
#include "VeNoDebugComponent.h"

class VeNoDebugScreen : public DocumentWindow
{
public:
    explicit VeNoDebugScreen (const std::string& pid);

    ~VeNoDebugScreen () override;

    void closeButtonPressed () override;

    void paint (Graphics& graphics) override;

    void resized () override;

private:
    std::string m_pid;
    std::shared_ptr<VeNoDebugComponent> component;
    std::unique_ptr<LookHandler> m_lookHandler;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (VeNoDebugScreen)

};

#endif //VENO_VENODEBUGSCREEN_H
