#pragma once

#include <vector>
#include "../GUI/Components/Base/VeNoKnob.h"
#include "../../vendor/tsl/robin_map.h"

namespace VeNo
{
    class ComponentStates
    {
    public:
        ComponentStates ();

        ~ComponentStates ();

        void addKnob (std::string name, VeNoKnob* knob);

        void removeKnob (std::string name);

        tsl::robin_map<std::string, VeNoKnob*> m_knobs;
    };
}