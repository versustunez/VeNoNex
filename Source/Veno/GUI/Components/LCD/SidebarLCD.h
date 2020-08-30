#ifndef VENO_SIDEBARLCD_H
#define VENO_SIDEBARLCD_H

#include "JuceHeader.h"
#include "../BaseComponent.h"
#include "Waveforms.h"
#include "../Config/VeNoActionButton.h"

class SidebarLCD : public BaseComponent
{
private:
public:
    explicit SidebarLCD (const std::string& process_id);

    ~SidebarLCD ();

    void resized () override;

    void paint (Graphics& g) override;

    std::shared_ptr<Waveforms> getWaveform ();

protected:
    void drawHeadline (Graphics& g);

    void drawFooter (Graphics& g);

    std::shared_ptr<Waveforms> m_waveform;
    std::unique_ptr<VeNoActionButton> m_configButton;
    std::unique_ptr<VeNoActionButton> m_matrixButton;
    std::unique_ptr<VeNoActionButton> m_debugButton;
    std::unique_ptr<VeNoActionButton> m_presetManager;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SidebarLCD);
};

#endif //VENO_SIDEBARLCD_H
