#include "OscillatorGUIHelper.h"
#include "../VenoInstance.h"

namespace VeNo
{
    std::shared_ptr<OscillatorGUIHelper> OscillatorGUIHelper::m_instance = nullptr;

    std::shared_ptr<OscillatorGUIHelper> OscillatorGUIHelper::getInstance ()
    {
        if (m_instance == nullptr)
            m_instance = std::make_shared<OscillatorGUIHelper> ();
        return m_instance;
    }

    void OscillatorGUIHelper::copy (const std::string& pid, const std::string& osc)
    {
        m_copyState.clear ();
        auto parameters = VenoInstance::getInstance (pid)->handler->getParameters ();
        for (auto& parameter : parameters)
        {
            if (parameter.first.rfind (osc) == 0)
            {
                auto param = parameter.first.substr (osc.length (), parameter.first.length ());
                m_copyState[param] = parameter.second->m_value;
            }
        }
    }

    void OscillatorGUIHelper::paste (const std::string& pid, const std::string& osc)
    {
        auto state = VenoInstance::getInstance (pid)->treeState;
        for (auto& parameter : m_copyState)
        {
            auto param = state->getParameter (osc + parameter.first);
            param->setValueNotifyingHost (param->convertTo0to1 (parameter.second));
        }
    }

    void OscillatorGUIHelper::solo (const std::string& pid, const std::string& osc)
    {
        auto state = VenoInstance::getInstance (pid)->treeState;
        for (int i = 1; i <= 4; ++i)
        {
            auto nOsc = "osc" + std::to_string (i);
            if (nOsc == osc)
            {
                state->getParameter (osc + "__active")->setValueNotifyingHost (1.0);
            }
            else
            {
                state->getParameter (nOsc + "__active")->setValueNotifyingHost (0);
            };
        }
    }
}