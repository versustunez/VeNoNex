//
// Created by versustune on 09.06.20.
//

#include "SynthInstance.h"
#include <utility>

SynthInstance::SynthInstance (std::string processId)
        : m_processId (std::move (processId))
{
}
