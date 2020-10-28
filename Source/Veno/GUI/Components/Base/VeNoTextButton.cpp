#include "VeNoTextButton.h"
#include "../../../Services/OscillatorGUIHelper.h"
#include "../../../Core/Config.h"

namespace VeNo
{
    VeNoTextButton::VeNoTextButton (const std::string& name, const std::string& text, const std::string& pid)
            : BaseComponent (pid), m_button (std::make_unique<juce::TextButton> (text))
    {
        m_button->setComponentID (name);
        m_button->addListener(this);
        setMouseCursor (MouseCursor::PointingHandCursor);
        addAndMakeVisible (*m_button);
    }

    void VeNoTextButton::resized ()
    {
        m_button->setBounds (0, 0, getWidth (), getHeight ());
    }

    void VeNoTextButton::paint (Graphics& g)
    {
        BaseComponent::paint (g);
    }

    void VeNoTextButton::setToCall (std::string toCall, std::string osc)
    {
        m_toCall = std::move (toCall);
        m_oscillator = std::move (osc);
    }

    void VeNoTextButton::buttonClicked (Button* button)
    {
        if (m_toCall == "call_copy")
        {
            OscillatorGUIHelper::getInstance ()->copy (m_processId, m_oscillator);
        }
        else if (m_toCall == "call_paste")
        {
            OscillatorGUIHelper::getInstance ()->paste (m_processId, m_oscillator);
        }
        else if (m_toCall == "call_solo")
        {
            OscillatorGUIHelper::getInstance ()->solo (m_processId, m_oscillator);
        }
    }

    void VeNoTextButton::buttonStateChanged (Button* button)
    {
    }

    VeNoTextButton::~VeNoTextButton ()
    {
        m_button.reset (nullptr);
    }
}