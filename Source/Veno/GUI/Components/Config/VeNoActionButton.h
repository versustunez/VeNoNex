#ifndef VENO_VENOACTIONBUTTON_H
#define VENO_VENOACTIONBUTTON_H

#include "JuceHeader.h"
#include "../BaseComponent.h"

class VeNoActionButton : public BaseComponent
{
public:
    enum ButtonType
    {
        Config = 0,
        Matrix,
        Debug,
        Presets
    };

    VeNoActionButton (const std::string& processId, std::string name, ButtonType type);

    ~VeNoActionButton () override = default;

    void paint (Graphics& g) override;

    void mouseDown (const MouseEvent& event) override;

    void handleConfig();
    void handleMatrix();
    void handleDebug();
    void handlePresets();

private:
    std::string m_name;
    ButtonType m_type;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (VeNoActionButton)
};

#endif //VENO_VENOACTIONBUTTON_H
