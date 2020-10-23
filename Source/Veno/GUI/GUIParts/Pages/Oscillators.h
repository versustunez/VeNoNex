#pragma once

#include "../../Components/BaseComponent.h"
#include "../../Components/Interfaces/TabInterface.h"

namespace VeNo
{
    class Oscillators : public BaseComponent, public TabInterface
    {
    public:
        Oscillators(const std::string& pid);
        ~Oscillators() override = default;

        void resized () override;

        void paint (Graphics& g) override;

        void updateColour () override;
        void updateSize () override;

    protected:
        std::unique_ptr<juce::TabbedComponent> m_tabbedComponent;
    };
}