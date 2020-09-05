#include "Limiter.h"
#include "../../../Utils.h"

namespace VeNo
{
    Limiter::Limiter (const std::string& name, std::shared_ptr<OscillatorParameters>& parameters)
            : m_name (name), m_parameters (parameters)
    {
    }

    void Limiter::apply (std::vector<double>& values, std::vector<double>& panned)
    {
        double threshold = m_parameters->m_limiterThreshold->getValueForVoice (m_parameters->m_index);
        switch (static_cast<int>(m_parameters->m_limiterMode->getBaseValue ()))
        {
            case 1:
                for (double& value : values)
                {
                    value = VeNo::Utils::clamp (value, -threshold, threshold);
                }
                break;
            case 2:
                for (int i = 0; i < 3; ++i)
                {
                    m_reducers[i].threshold = threshold;
                    values[i] = m_reducers[i].limit(values[i]);
                }
                break;
        }

    }
}