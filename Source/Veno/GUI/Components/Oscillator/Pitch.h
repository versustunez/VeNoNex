#pragma once

#include "../BaseComponent.h"
#include "../Base/VeNoKnob.h"

namespace VeNo
{
    class Pitch : public BaseComponent
    {
    public:
        Pitch (const std::string& name, const std::string& pid);

        ~Pitch () override = default ;

        void resized () override;

        void paint (Graphics& g) override;

    protected:
        std::string m_name;
        std::unique_ptr<VeNoKnob> m_semitones;
        std::unique_ptr<VeNoKnob> m_fineTune;
    };
}