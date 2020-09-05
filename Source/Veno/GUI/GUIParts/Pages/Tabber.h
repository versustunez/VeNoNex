#pragma once

#include "JuceHeader.h"
#include "../../Components/BaseComponent.h"

namespace VeNo
{
    class Tabber : public BaseComponent
    {
    public:
        Tabber (const std::string& pid);

        ~Tabber () override = default;

        void resized () override;

        void paint (Graphics& g) override;

    protected:
        std::string m_name;
        std::unique_ptr<juce::TabbedComponent> m_tabbedComponent;
    };
}