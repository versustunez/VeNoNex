#pragma once

#include <string>
#include "../BaseComponent.h"
#include "../Base/VeNoKnob.h"
#include "../Base/VeNoTextButton.h"

namespace VeNo
{
    class GuiMatrixItem : public BaseComponent, public juce::Button::Listener, public juce::Slider::Listener
    {
    public:
        GuiMatrixItem (std::string& pid, std::string key);

        ~GuiMatrixItem () override;

        void resized () override;

        void paint (Graphics& g) override;

        void buttonClicked (Button* button) override;

        void buttonStateChanged (Button* button) override;

        void sliderValueChanged (Slider* slider) override;

        void sliderDragStarted (Slider* slider) override;

        void sliderDragEnded (Slider* slider) override;

        std::string m_key;
    protected:
        std::unique_ptr<juce::Label> m_modulator;
        std::unique_ptr<juce::Label> m_modulation;
        std::unique_ptr<VeNoKnob> m_amount;
        std::unique_ptr<VeNoTextButton> m_btn;
    };
}