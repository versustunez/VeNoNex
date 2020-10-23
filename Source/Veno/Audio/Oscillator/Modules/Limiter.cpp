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
        // hard limit at 6dB!
        for (double& value : values)
        {
            value = value > 2 ? 2 : value < -2 ? -2 : value;
        }
    }
}