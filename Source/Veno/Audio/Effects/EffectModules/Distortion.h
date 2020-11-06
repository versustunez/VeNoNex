#pragma once

#include "../Effect.h"
#include "../../Engine/VeNoParameter.h"
#include "../../Modules/Filter.h"

namespace VeNo
{
    class Distortion : public Effect
    {
    public:
        explicit Distortion (std::string pid);

        // we dont need to delete the pointers! because they are deleted in the ParameterHandler after Shutdown
        ~Distortion () override = default;

        void prepare () override;

        void process (AudioBuffer<float>& audioBuffer) override;

    protected:
        VeNo::Filter m_preLP;
        VeNo::Filter m_preHP;
        VeNo::Filter m_postLP;
        VeNo::Filter m_postHP;
        VeNoParameter* m_inputGain{};
        VeNoParameter* m_outputGain{};
        VeNoParameter* m_preLPValue{};
        VeNoParameter* m_preHPValue{};
        VeNoParameter* m_postLPValue{};
        VeNoParameter* m_postHPValue{};
        VeNoParameter* m_drive{};
        VeNoParameter* m_type{};
        VeNoParameter* m_dynamic{}; // can different for specific distortion types like tube
        VeNoParameter* m_mix{};
    };
}