#pragma once

#include "JuceHeader.h"
#include "Effect.h"
#include "../../Core/VeNoListener.h"

namespace VeNo
{
    class EffectSeries
    {
    public:
        explicit EffectSeries(std::string  pid);
        ~EffectSeries();
        void process(AudioBuffer<float>& buffer);
    protected:
        std::string m_pid;
        std::vector<Effect*> m_effects;
    };
}