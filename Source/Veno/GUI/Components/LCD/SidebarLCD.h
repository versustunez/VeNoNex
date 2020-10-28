#ifndef VENO_SIDEBARLCD_H
#define VENO_SIDEBARLCD_H

#include "JuceHeader.h"
#include "../BaseComponent.h"
#include "../Config/VeNoActionButton.h"
#include "LCDComponents/WaveForms.h"
#include "LCDComponents/DecibelScale.h"
#include "../../../Audio/Engine/VeNoParameter.h"
#include "../../../Core/VeNoListener.h"
#include "LCDComponents/LCDParameters.h"

class SidebarLCD : public BaseComponent,
                   public VeNoListener,
                   private AsyncUpdater
{
private:
public:
    explicit SidebarLCD (const std::string& process_id);

    ~SidebarLCD () override;

    void resized () override;

    void paint (Graphics& g) override;

    void parameterChanged (VeNoParameter* parameter) override;

    void notify (const std::string& name, double value) override;

    void mouseDown (const MouseEvent& event) override;

private:
    void handleAsyncUpdate () override;

protected:
    void drawHeadline (Graphics& g);

    void drawFooter (Graphics& g);

    void getState ();

    std::shared_ptr<VeNo::WaveFormsGui> m_waveform;
    std::unique_ptr<DecibelScale> m_dBScale;
    std::unique_ptr<VeNo::LCDParameters> m_parameterScreen;
    std::unique_ptr<VeNoActionButton> m_configButton;
    std::unique_ptr<VeNoActionButton> m_matrixButton;
    std::unique_ptr<VeNoActionButton> m_debugButton;
    std::unique_ptr<VeNoActionButton> m_presetManager;
    double m_lastNotifyValue = -1;
    int m_mode = -1;
    bool m_needClear = false;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SidebarLCD);
};

#endif //VENO_SIDEBARLCD_H
