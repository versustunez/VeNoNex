#pragma once

#include "../../BaseComponent.h"
#include "../../../../Services/GUIHelper.h"

namespace VeNo
{
    class EnvelopeGuiPart : public GUICreator
    {
    public:
        EnvelopeGuiPart (std::string label, std::string name, const std::string& pid);

        ~EnvelopeGuiPart () override;

        void resized () override;

        void paint (Graphics& g) override;

        void setupGui() override;

    protected:
        std::string m_name;
        std::string m_label;
        std::unique_ptr<GUIHelper> m_helper;
    };
}