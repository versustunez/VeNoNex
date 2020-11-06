#include "Effect.h"

namespace VeNo
{
    Effect::Effect (std::string pid)
            : m_processId (std::move (pid))
    {}
}