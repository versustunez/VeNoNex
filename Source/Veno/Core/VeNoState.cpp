#include "VeNoState.h"

VeNoState::VeNoState (std::string pid)
{
    m_pid = pid;
}

VeNoState::~VeNoState ()
{
    delete configScreen;
    configScreen = nullptr;
}
