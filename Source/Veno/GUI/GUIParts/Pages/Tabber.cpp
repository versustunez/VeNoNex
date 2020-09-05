#include "Tabber.h"
#include "../../../Core/Config.h"
#include "Oscillators.h"
#include "../../../Utils.h"

namespace VeNo
{
    Tabber::Tabber (const std::string& pid)
            : BaseComponent (pid), m_tabbedComponent (
            std::make_unique<juce::TabbedComponent> (juce::TabbedButtonBar::Orientation::TabsAtTop))
    {
        auto theme = Config::getInstance ()->getCurrentTheme ();
        m_tabbedComponent->addTab ("Oscillators", theme->getColour (ThemeColour::bg), new Oscillators (m_processId),
                                   true, -1);
        m_tabbedComponent->setTabBarDepth(Utils::getScaledSize(30));
        m_tabbedComponent->setOutline(0);
        addAndMakeVisible (*m_tabbedComponent);
    }

    void Tabber::resized ()
    {
        m_tabbedComponent->setBounds (0, 0, getWidth (), getHeight ());
    }

    void Tabber::paint (Graphics& g)
    {
    }
}