#pragma once

#include "JuceHeader.h"
#include "../../Components/BaseComponent.h"
#include "../../Components/Interfaces/TabInterface.h"

namespace VeNo
{
    class Tabber : public BaseComponent, public TabInterface
    {
    public:
        Tabber (const std::string& pid);

        ~Tabber () override;

        void resized () override;

        void paint (Graphics& g) override;

        void updateColour () override;
        void updateSize () override;

    protected:
        std::string m_name;
        std::unique_ptr<juce::TabbedComponent> m_tabbedComponent;
        std::vector<TabInterface*> m_components;
    };
}