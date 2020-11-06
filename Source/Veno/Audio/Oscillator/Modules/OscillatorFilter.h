#pragma once

#include "../../Modules/Filter.h"
#include "../../Engine/VeNoParameter.h"

namespace VeNo
{
    class OscillatorFilter
    {
    public:
        OscillatorFilter(std::string id, const std::string& name);
        ~OscillatorFilter();
        void update();
        VeNo::Filter m_filter;
        int m_voice = -1;
    protected:
        std::string m_pid;
        std::string m_name;
        VeNoParameter* m_qFactor;
        VeNoParameter* m_cutOff;
        VeNoParameter* m_type;
    };

}
