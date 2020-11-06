#include "ModulatorPage.h"
#include "../../../Core/Config.h"
#include "../../../Utils.h"
#include "../../Components/PageComponents/Modulators/LFOPage.h"
#include "../../Components/PageComponents/Modulators/EnvelopePage.h"

namespace VeNo
{
    ModulatorPage::ModulatorPage (const std::string& pid) : BaseComponent (pid),
                                                        m_tabbedComponent (std::make_unique<juce::TabbedComponent> (
                                                                juce::TabbedButtonBar::Orientation::TabsAtTop))
    {
        auto theme = Config::getInstance ()->getCurrentTheme ();
        for (int i = 1; i <= 2; ++i)
        {
            m_tabbedComponent->addTab ("LFO" + std::to_string (i), theme->getColour (ThemeColour::bg_two),
                                       new LFOPage ("lfo" + std::to_string (i), m_processId), true, -1);
        }
        m_tabbedComponent->addTab ("Envelopes", theme->getColour (ThemeColour::bg_two),
                                   new EnvelopePage ("Envelopes", m_processId), true, -1);
        m_tabbedComponent->setTabBarDepth (Utils::getScaledSize (30));
        m_tabbedComponent->setIndent(Utils::getScaledSize(5));
        m_tabbedComponent->setOutline(0);
        addAndMakeVisible (*m_tabbedComponent);
    }

    void ModulatorPage::resized ()
    {
        if (m_tabbedComponent != nullptr)
        {
            m_tabbedComponent->setBounds (0, 0, getWidth (), getHeight ());
        }
    }

    void ModulatorPage::paint (Graphics& g)
    {
    }

    void ModulatorPage::updateColour ()
    {
        auto theme = Config::getInstance ()->getCurrentTheme ();
        auto tabs = m_tabbedComponent->getNumTabs();
        for (int i = 0; i < tabs; ++i)
        {
            m_tabbedComponent->setTabBackgroundColour(i, theme->getColour(ThemeColour::bg_two));
        }
    }

    void ModulatorPage::updateSize ()
    {
        m_tabbedComponent->setTabBarDepth(Utils::getScaledSize(30));
    }
}