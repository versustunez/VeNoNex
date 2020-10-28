#include "Oscillators.h"
#include "../../../Core/Config.h"
#include "../../Components/PageComponents/Oscillators/OscillatorPage.h"
#include "../../../Utils.h"
#include "../../../VenoInstance.h"

namespace VeNo
{
    Oscillators::Oscillators (const std::string& pid) : juce::TabbedComponent (
            juce::TabbedButtonBar::Orientation::TabsAtTop), m_processId(pid)
    {
        auto theme = Config::getInstance ()->getCurrentTheme ();
        for (int i = 1; i <= 4; ++i)
        {
            addTab ("OSC" + std::to_string (i), theme->getColour (ThemeColour::bg_two),
                    new OscillatorPage ("osc" + std::to_string (i), m_processId), true, -1);
        }
        setTabBarDepth (Utils::getScaledSize (30));
        setCurrentTabIndex(0);
        setOutline (0);
    }

    void Oscillators::updateColour ()
    {
        auto theme = Config::getInstance ()->getCurrentTheme ();
        auto tabs = getNumTabs ();
        for (int i = 0; i < tabs; ++i)
        {
            setTabBackgroundColour (i, theme->getColour (ThemeColour::bg_two));
        }
    }

    void Oscillators::updateSize ()
    {
        setTabBarDepth (Utils::getScaledSize (30));
    }

    void Oscillators::currentTabChanged (int newCurrentTabIndex, const String& newCurrentTabName)
    {
        VenoInstance::getInstance (m_processId)->state->currentOscillator = newCurrentTabIndex + 1;
    }
}