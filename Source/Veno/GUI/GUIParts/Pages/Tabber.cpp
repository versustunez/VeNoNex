#include "Tabber.h"
#include "../../../Core/Config.h"
#include "Oscillators.h"
#include "../../../Utils.h"
#include "ModulatorPage.h"

namespace VeNo
{
    Tabber::Tabber (const std::string& pid)
            : BaseComponent (pid), m_tabbedComponent (
            std::make_unique<juce::TabbedComponent> (juce::TabbedButtonBar::Orientation::TabsAtTop))
    {
        auto theme = Config::getInstance ()->getCurrentTheme ();
        auto osc = new Oscillators (m_processId);
        auto modulators = new ModulatorPage (m_processId);
        m_components.push_back (osc);
        m_components.push_back (modulators);
        m_tabbedComponent->addTab ("Oscillators", theme->getColour (ThemeColour::bg), osc, true, -1);
        m_tabbedComponent->addTab ("Modulators", theme->getColour (ThemeColour::bg), modulators, true, -1);
        m_tabbedComponent->setTabBarDepth (Utils::getScaledSize (30));
        m_tabbedComponent->setOutline (0);
        m_tabbedComponent->setCurrentTabIndex(0, false);
        addAndMakeVisible (*m_tabbedComponent);
    }

    void Tabber::resized ()
    {
        m_tabbedComponent->setBounds (0, 0, getWidth (), getHeight ());
        m_tabbedComponent->setCurrentTabIndex (m_tabbedComponent->getCurrentTabIndex ());
    }

    void Tabber::paint (Graphics& g)
    {
    }

    void Tabber::updateColour ()
    {
        auto theme = Config::getInstance ()->getCurrentTheme ();
        auto tabs = m_tabbedComponent->getNumTabs ();
        for (int i = 0; i < tabs; ++i)
        {
            m_tabbedComponent->setTabBackgroundColour (i, theme->getColour (ThemeColour::bg));
            m_components[i]->updateColour ();
        }
    }

    void Tabber::updateSize ()
    {
        m_tabbedComponent->setTabBarDepth (Utils::getScaledSize (30));
        auto tabs = m_tabbedComponent->getNumTabs ();
        for (int i = 0; i < tabs; ++i)
        {
            m_components[i]->updateSize ();
        }
    }

    Tabber::~Tabber ()
    {
        m_tabbedComponent.reset (nullptr);
        m_components.clear ();
    }
}