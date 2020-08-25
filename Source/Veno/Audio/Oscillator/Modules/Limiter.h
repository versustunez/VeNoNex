#ifndef VENO_LIMITER_H
#define VENO_LIMITER_H

#include <vector>
#include "../../../Core/ParameterHandler.h"
#include "../Helper/OscillatorParameters.h"

class Limiter
{
private:
public:
private:
    std::string m_name;
    std::shared_ptr<OscillatorParameters> m_parameters;
public:
    explicit Limiter (const std::string& name, std::shared_ptr<OscillatorParameters>& parameters);

    ~Limiter () = default;

    void apply (std::vector<float>& values, std::vector<float>& panned);
};


#endif //VENO_LIMITER_H
