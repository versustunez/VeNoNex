#ifndef VENO_WIDENER_H
#define VENO_WIDENER_H

#define SQRT2_2 0.70710678118
#include "../../../Core/ParameterHandler.h"
#include "../Helper/OscillatorParameters.h"

class Widener
{
private:
    std::string m_name;
    std::shared_ptr<OscillatorParameters> m_parameters;
    float m_panning[2] = {SQRT2_2, SQRT2_2};
public:
    explicit Widener(const std::string& name, std::shared_ptr<OscillatorParameters>& parameters);
    ~Widener() = default;
    void update();
    void apply(std::vector<float> &values, std::vector<float> &panned);
    void applyPanning(std::vector<float> &values, std::vector<float> &panned);
    float getDetunePan();
    float m_coefficientM;
    float m_coefficient;
    float m_coefficientDetune;
    float m_wide;
    float m_lastPanning;
};

#undef SQRT2_2
#endif //VENO_WIDENER_H
