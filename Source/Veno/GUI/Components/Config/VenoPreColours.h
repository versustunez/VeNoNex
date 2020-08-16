//
// Created by versustune on 14.06.20.
//

#ifndef VENO_VENOPRECOLOURS_H
#define VENO_VENOPRECOLOURS_H

#include "JuceHeader.h"
#include "../../Components/BaseComponent.h"

class VenoPreColours : public BaseComponent, public Slider::Listener, Button::Listener
{
public:
    VenoPreColours (const std::string& processId);
    ~VenoPreColours();
    void initSliders();
    void initButtons();
    void sliderValueChanged (Slider* slider) override;
    void resized () override;
private:
    void buttonClicked (Button* button) override;
protected:
    std::shared_ptr<Slider> m_fpsSlider;
    std::shared_ptr<Slider> m_scaleSlider;
    std::vector<std::unique_ptr<TextButton>> m_pre;
    std::string m_names[4]{
            "LED", "Blood", "Orange Dream", "Ocean"
    };
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (VenoPreColours)
};
#endif //VENO_VENOPRECOLOURS_H
