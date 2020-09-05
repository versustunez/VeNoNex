#include "VeNoState.h"

VeNoState::VeNoState (const std::string& pid)
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
