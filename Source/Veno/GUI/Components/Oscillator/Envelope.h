#pragma once

#include "../BaseComponent.h"
#include "../Base/VeNoKnob.h"

namespace VeNo
{
    class Envelope : public BaseComponent
    {
    public:
        Envelope(const std::string& name, const std::string& pid);
        ~Envelope() override = default;

        void resized () override;

        void paint (Graphics& g) override;

    protected:
        std::string m_name;
        std::unique_ptr<VeNoKnob> m_attack;
        std::unique_ptr<VeNoKnob> m_decay;
        std::unique_ptr<VeNoKnob> m_sustain;
        std::unique_ptr<VeNoKnob> m_release;
    };
}