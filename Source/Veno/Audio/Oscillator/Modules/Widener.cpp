#include "Widener.h"
#include "../../../Utils/VeNoParameterStringHelper.h"

#define PI_4 0.78539816339
#define SQRT2_2 0.70710678118

Widener::Widener(const std::string& name, std::shared_ptr<OscillatorParameters>& parameters)
{
    m_name = name;
    m_parameters = parameters;
}

void Widener::apply(std::vector<float>& values, std::vector<float>& panned)
{
    float mid = (panned[0] + panned[1]) * m_coefficientM;
    float stereo = (panned[1] - panned[0]) * m_coefficient;
    values[1] = mid - stereo;
    values[2] = mid + stereo;
    applyPanning(values, panned);
}

float Widener::getDetunePan()
{
    return m_coefficientDetune;
}

void Widener::update()
{
    auto wide = m_parameters->m_stereo->getValue();
    if (m_wide != wide)
    {
        float _width = wide / 200;
        float tmp = 1 / fmax(1 + _width, 2);
        m_coefficientM = 1 * tmp;
        m_coefficient = _width * tmp;
        m_coefficientDetune = m_coefficient * .3;
        m_wide = wide;
    }
    auto panning = m_parameters->m_panning->getValue();
    if (panning != m_lastPanning)
    {
        float angle = panning * PI_4;
        m_panning[0] = SQRT2_2 * double(std::cos(angle) - std::sin(angle));
        m_panning[1] = SQRT2_2 * double(std::cos(angle) + std::sin(angle));
        m_lastPanning = panning;
    }


}

void Widener::applyPanning(std::vector<float>& values, std::vector<float>& panned)
{
    float mono = values[0];
    values[1] = (m_panning[0] * (mono + values[1]));
    values[2] = (m_panning[1] * (mono + values[2]));
}

#undef PI_4
#undef SQRT2_2