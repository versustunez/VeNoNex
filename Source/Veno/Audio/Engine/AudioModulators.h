#pragma once

#include <vector>
#include "Modulator.h"

namespace VeNo
{
    class AudioModulators
    {
    public:
        AudioModulators(const std::string& processId);
        ~AudioModulators();
        void init();
    protected:
        std::vector<Modulator*> m_modulators;
        std::string m_pid;
    };
}