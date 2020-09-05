#pragma once

#include "../BaseComponent.h"
#include "../Base/VeNoSelect.h"
#include "../Base/VeNoKnob.h"

namespace VeNo
{
    /**
     * GUI Class that will hold all settings for the Unison Voices
     * this means: Mode, Amount, Stereo, Dense
     */
    class Unison : public BaseComponent
    {
    public:
        Unison(const std::string& name, const std::string& pid);
        ~Unison () override = default;

        void resized () override;

        void paint (Graphics& g) override;

    protected:
        std::string m_name;
        std::unique_ptr<VeNoSelect> m_modeSelector;
        std::unique_ptr<VeNoKnob> m_amount;
        std::unique_ptr<VeNoKnob> m_dense;
        std::unique_ptr<VeNoKnob> m_stereo;
        std::unique_ptr<VeNoKnob> m_voices;
    };
}