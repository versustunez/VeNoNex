#pragma once

#include "../BaseComponent.h"
#include "../Base/VeNoSelect.h"
#include "../Base/VeNoKnob.h"

namespace VeNo
{
    class WaveformControl : public BaseComponent
    {
    public:
        WaveformControl(const std::string& name, const std::string& pid);
        ~WaveformControl () override = default;

        void resized () override;

        void paint (Graphics& g) override;

    protected:
        std::string m_name;
        std::unique_ptr<VeNoSelect> m_baseForm;
        std::unique_ptr<VeNoSelect> m_secondForm;
        std::unique_ptr<VeNoKnob> m_mixKnob;
    };
}