#ifndef VENO_VENOCOMPONENTLISTENER_H
#define VENO_VENOCOMPONENTLISTENER_H

#include "JuceHeader.h"

class VeNoComponentListener : public Slider::Listener,
                              public ComboBox::Listener,
                              public ToggleButton::Listener,
                              public MouseListener
{
public:
    explicit VeNoComponentListener (std::string pid);

    void buttonClicked (Button* button) override;

    void comboBoxChanged (ComboBox* comboBoxThatHasChanged) override;

    void sliderValueChanged (Slider* slider) override;

    void sliderDragStarted (Slider* slider) override;

    void sliderDragEnded (Slider* slider) override;

protected:
    std::string m_pid;
    bool m_sliderChanging = false;
};


#endif //VENO_VENOCOMPONENTLISTENER_H
