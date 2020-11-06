#include "EffectSeries.h"
#include "../../VenoInstance.h"

#include <utility>

namespace VeNo
{
    EffectSeries::EffectSeries (std::string pid)
            : m_pid (std::move (pid))
    {
    }

    EffectSeries::~EffectSeries ()
    {
        for (auto& effect : m_effects)
        {
            delete effect;
        }
    };

    void EffectSeries::process (AudioBuffer<float>& buffer)
    {
        for (auto& effect : m_effects)
        {
            effect->prepare();
            if (effect->isActive)
                effect->process (buffer);
        }
    }
}