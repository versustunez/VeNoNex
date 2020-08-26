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
    explicit Widener (const std::string& name, std::shared_ptr<OscillatorParameters>& parameters);

    ~Widener () = default;

    void update ();

    void apply (std::vector<float>& values, std::vector<float>& panned);

    void applyPanning (std::vector<float>& values, std::vector<float>& panned);

    float getDetunePan ();

    float m_coefficientM = 0.0f;
    float m_coefficient = 0.0f;
    float m_coefficientDetune = 0.0f;
    float m_wide = 0;
    float m_lastPanning = 0;
};

#undef SQRT2_2
#endif //VENO_WIDENER_H
