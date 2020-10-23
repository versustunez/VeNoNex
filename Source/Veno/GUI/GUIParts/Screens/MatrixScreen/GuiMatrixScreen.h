#pragma once

#include <string>
#include "../../../../Core/Config.h"
#include "GuiMatrixComponent.h"

namespace VeNo
{
    class GuiMatrixScreen : public DocumentWindow
    {
    private:
        std::string m_pid;
        std::unique_ptr<LookHandler> m_lookHandler;
        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (GuiMatrixScreen)
    public:
        explicit GuiMatrixScreen (const std::string& pid);

        ~GuiMatrixScreen () override;

        void closeButtonPressed () override;

        void paint (Graphics& graphics) override;

        void resized () override;

        std::shared_ptr<GuiMatrixComponent> m_component;
    };
}