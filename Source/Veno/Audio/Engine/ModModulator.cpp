#include "ModModulator.h"
#include "../../VenoInstance.h"

ModModulator::ModModulator (std::string name, const std::string& showName, std::string pid)
        : m_pid (std::move (pid)), m_name (std::move (name))
{
    m_showName = showName;
    m_mod = VenoInstance::getInstance (m_pid)->handler->getParameter (m_name);
}

ModModulator::~ModModulator ()
= default;

double ModModulator::getValue ()
{
    return Modulator::getValue ();
}

void ModModulator::update ()
{
    if (m_mod != nullptr)
    {
        m_value = m_mod->getBaseValue ();
    }
}
