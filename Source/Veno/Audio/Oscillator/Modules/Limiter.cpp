#include "Limiter.h"
#include "../../../Utils.h"

Limiter::Limiter (const std::string& name, std::shared_ptr<OscillatorParameters>& parameters)
{
    m_name = name;
    m_parameters = parameters;
}

void Limiter::apply (std::vector<double>& values, std::vector<double>& panned)
{
    for (double& value : values)
    {
        value = VeNo::Utils::clamp (value, -1, 1);
    }
}
