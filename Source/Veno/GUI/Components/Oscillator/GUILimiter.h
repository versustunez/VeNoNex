#pragma once

#include "../BaseComponent.h"

namespace VeNo
{
    class GUILimiter : public BaseComponent
    {
    public:
        GUILimiter(const std::string& name, const std::string& pid);
        ~GUILimiter() override = default;

        void resized () override;

        void paint (Graphics& g) override;

    protected:
        std::string m_name;
    };
}