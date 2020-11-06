#pragma once

#include <string>
#include "../../BaseComponent.h"
#include "../../../../Services/GUIHelper.h"
#include "EnvelopeGuiPart.h"

namespace VeNo
{
    class EnvelopePage : public BaseComponent
    {
    public:
        EnvelopePage (std::string  name, const std::string& pid);

        ~EnvelopePage () override;

        void resized () override;

        void paint (Graphics& g) override;

    protected:
        std::string m_name;
        std::vector<std::unique_ptr<EnvelopeGuiPart>> m_guiParts;
    };
}