#ifndef VENO_VENOCONFIGSCREEN_H
#define VENO_VENOCONFIGSCREEN_H

#include "JuceHeader.h"
#include "../../../../Core/Config.h"
#include "../../../Components/Config/VeNoColour.h"
#include "ConfigComponent.h"

class VenoConfigScreen : public DocumentWindow
{
public:
    explicit VenoConfigScreen (const std::string& pid);

    ~VenoConfigScreen () override;

    void closeButtonPressed () override;

    void paint (Graphics& graphics) override;

    void resized () override;

private:
    std::string m_pid;
    std::shared_ptr<ConfigComponent> component;
    std::unique_ptr<LookHandler> m_lookHandler;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (VenoConfigScreen)

};

#endif //VENO_VENOCONFIGSCREEN_H
