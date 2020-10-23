#pragma once

#include "../BaseComponent.h"

namespace VeNo
{
    class VeNoTextButton : public BaseComponent, public juce::Button::Listener
    {
    public:
        VeNoTextButton (const std::string& name, const std::string& text, const std::string& pid);

        ~VeNoTextButton () override;

        void resized () override;

        void paint (Graphics& g) override;

        void setToCall (std::string toCall, std::string osc);

        void buttonClicked (Button* button) override;

        void buttonStateChanged (Button* button) override;

        std::unique_ptr<juce::TextButton> m_button;
    protected:
        std::string m_oscillator = "";
        std::string m_toCall = "";
    };
}