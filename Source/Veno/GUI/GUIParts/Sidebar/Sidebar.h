#ifndef VENO_SIDEBAR_H
#define VENO_SIDEBAR_H

#include "JuceHeader.h"
#include "../../Components/BaseComponent.h"
#include "../../Components/LCD/SidebarLCD.h"
#include "SidebarMixer.h"

class Sidebar : public BaseComponent
{
private:
public:
    Sidebar (const std::string& processId);

    ~Sidebar () override;

    void resized () override;

    void paint (Graphics& g) override;

    std::shared_ptr<Waveforms> getWaveform ();

protected:
    std::unique_ptr<SidebarLCD> m_lcd;
    std::unique_ptr<SidebarMixer> m_mixer;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Sidebar)
};

#endif //VENO_SIDEBAR_H
