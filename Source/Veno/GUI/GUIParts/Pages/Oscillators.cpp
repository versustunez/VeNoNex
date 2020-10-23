#include "Oscillators.h"
#include "../../../Core/Config.h"
#include "../../Components/PageComponents/Oscillators/OscillatorPage.h"
#include "../../../Utils.h"

namespace VeNo
{
    Oscillators::Oscillators (const std::string& pid) : BaseComponent (pid),
                                                        m_tabbedComponent (std::make_unique<juce::TabbedComponent> (
                                                                juce::TabbedButtonBar::Orientation::TabsAtTop))
    {
        auto theme = Config::getInstance ()->getCurrentTheme ();
        for (int i = 1; i <= 4; ++i)
        {
            m_tabbedComponent->addTab ("OSC" + std::to_string (i), theme->getColour (ThemeColour::bg_two),
                                       new OscillatorPage ("osc" + std::to_string (i), m_processId), true, -1);
        }
        m_tabbedComponent->setTabBarDepth (Utils::getScaledSize (30));
        m_tabbedComponent->setOutline (0);
        addAndMakeVisible (*m_tabbedComponent);
    }

    void Oscillators::resized ()
    {
        if (m_tabbedComponent != nullptr)
        {
            m_tabbedComponent->setBounds (0, 0, getWidth (), getHeight ());
            m_tabbedComponent->setCurrentTabIndex (m_tabbedComponent->getCurrentTabIndex ());
        }
    }

    void Oscillators::paint (Graphics& g)
    {
    }

    void Oscillators::updateColour ()
    {
        auto theme = Config::getInstance ()->getCurrentTheme ();
        auto tabs = m_tabbedComponent->getNumTabs ();
        for (int i = 0; i < tabs; ++i)
        {
            m_tabbedComponent->setTabBackgroundColour (i, theme->getColour (ThemeColour::bg_two));
        }
    }

    void Oscillators::updateSize ()
    {
        m_tabbedComponent->setTabBarDepth (Utils::getScaledSize (30));
    }
}