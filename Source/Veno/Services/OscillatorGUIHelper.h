#pragma once

#include <memory>
#include <unordered_map>

namespace VeNo
{
    class OscillatorGUIHelper
    {
        static std::shared_ptr<OscillatorGUIHelper> m_instance;
    public:
        static std::shared_ptr<OscillatorGUIHelper> getInstance ();

        void copy (const std::string& pid, const std::string& osc);
        void paste (const std::string& pid, const std::string& osc);
        void solo (const std::string& pid, const std::string& osc);

    protected:
        std::unordered_map<std::string, double> m_copyState;
    };
}