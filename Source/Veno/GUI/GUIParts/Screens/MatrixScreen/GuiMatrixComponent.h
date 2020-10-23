#pragma once

#include <string>
#include "JuceHeader.h"
#include "../../../Components/Matrix/GuiMatrixFooter.h"
#include "../../../Components/Matrix/GuiMatrixList.h"

namespace VeNo
{
    class GuiMatrixComponent : public Viewport
    {
    protected:
        std::string m_pid;
        std::unique_ptr<GuiMatrixFooter> m_footer;
        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (GuiMatrixComponent)
    public:
        explicit GuiMatrixComponent(std::string& pid);

        ~GuiMatrixComponent () override;

        void paint (Graphics& g) override;

        void resized () override;
        std::unique_ptr<GuiMatrixList> m_list;
    };
}