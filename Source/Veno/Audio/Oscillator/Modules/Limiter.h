#pragma once

#include <vector>
#include "../../../Core/ParameterHandler.h"
#include "../Helper/OscillatorParameters.h"
#include "SubModules/PeakReducer.h"

namespace VeNo {
    class Limiter
    {
    private:
        std::string m_name;
        std::shared_ptr<OscillatorParameters> m_parameters;
        std::vector<PeakReducer> m_reducers{3};
    public:
        explicit Limiter (const std::string& name, std::shared_ptr<OscillatorParameters>& parameters);

        ~Limiter () = default;

        void apply (std::vector<double>& values, std::vector<double>& panned);
    };
}