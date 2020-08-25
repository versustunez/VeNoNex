#include "Limiter.h"
#include "../../../Utils.h"

Limiter::Limiter (const std::string& name, std::shared_ptr<OscillatorParameters>& parameters)
{
    m_name = name;
    m_parameters = parameters;
}

void Limiter::apply (std::vector<float>& values, std::vector<float>& panned)
{
    for (float& value : values)
    {
        value = VeNo::Utils::clamp (value, -1, 1);
    }
}
