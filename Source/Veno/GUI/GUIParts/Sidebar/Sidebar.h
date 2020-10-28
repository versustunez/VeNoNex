#ifndef VENO_SIDEBAR_H
#define VENO_SIDEBAR_H

#include "JuceHeader.h"
#include "../../Components/BaseComponent.h"
#include "../../Components/LCD/SidebarLCD.h"
#include "SidebarMixer.h"
#include "ModMixer.h"
#include "PresetManagerComponent.h"

class Sidebar : public BaseComponent
{
private:
public:
    Sidebar (const std::string& processId);

    ~Sidebar () override;

    void resized () override;

    void paint (Graphics& g) override;

protected:
    std::unique_ptr<SidebarLCD> m_lcd;
    std::unique_ptr<SidebarMixer> m_mixer;
    std::unique_ptr<ModMixer> m_modMixer;
    std::unique_ptr<VeNoKnob> m_volumeKnob;
    std::unique_ptr<PresetManagerComponent> m_preset;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Sidebar)
};

#endif //VENO_SIDEBAR_H
