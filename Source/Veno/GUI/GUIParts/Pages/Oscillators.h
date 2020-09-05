#pragma once

#include "../../Components/BaseComponent.h"

namespace VeNo
{
    class Oscillators : public BaseComponent
    {
    public:
        Oscillators(const std::string& pid);
        ~Oscillators() override = default;

        void resized () override;

        void paint (Graphics& g) override;

    protected:
        std::unique_ptr<juce::TabbedComponent> m_tabbedComponent;
    };
}