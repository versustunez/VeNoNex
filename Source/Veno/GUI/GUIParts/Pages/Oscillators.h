#pragma once

#include "../../Components/BaseComponent.h"
#include "../../Components/Interfaces/TabInterface.h"

namespace VeNo
{
    class Oscillators : public TabInterface, public juce::TabbedComponent
    {
    public:
        explicit Oscillators (const std::string& pid);

        ~Oscillators () override = default;

        void updateColour () override;

        void updateSize () override;

    private:
        std::string m_processId;
        void currentTabChanged (int newCurrentTabIndex, const String& newCurrentTabName) override;
    };
}