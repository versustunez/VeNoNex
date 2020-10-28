#pragma once

#include "../BaseComponent.h"
#include "../Base/VeNoSelect.h"
#include "../Base/VeNoTextButton.h"

namespace VeNo
{
    class GuiMatrixFooter : public BaseComponent, public juce::Button::Listener
    {
    public:
        explicit GuiMatrixFooter (std::string& pid);

        ~GuiMatrixFooter () override;

        void resized () override;

        void paint (Graphics& g) override;

        void buttonClicked (Button* button) override;

        void buttonStateChanged (Button* button) override;

        void createParameterSelection();

    protected:
        std::unique_ptr<VeNoSelect> m_modulatorSelect;
        std::unique_ptr<VeNoSelect> m_modulationSelect;
        std::unique_ptr<VeNoTextButton> m_addButton;
        std::vector<std::string> m_modulators;
        std::vector<std::string> m_modulations;

        void initMatrix ();
    };
}