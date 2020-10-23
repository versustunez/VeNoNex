#include "ComponentStates.h"

namespace VeNo
{
    ComponentStates::ComponentStates ()
    {

    }

    ComponentStates::~ComponentStates ()
    {
        m_knobs.clear ();
    }

    void ComponentStates::addKnob (std::string name, VeNoKnob* knob)
    {
        m_knobs[name] = knob;
    }

    void ComponentStates::removeKnob (std::string name)
    {
        if (m_knobs.contains (name))
        {
            m_knobs.erase(name);
        }
    }
}