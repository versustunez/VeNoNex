#include "VeNoState.h"

VeNoState::VeNoState (std::string pid)
        : m_pid (pid)
{
}

VeNoState::~VeNoState ()
{
    delete configScreen;
    delete debugScreen;
    configScreen = nullptr;
    debugScreen = nullptr;
}
