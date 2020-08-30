#include "VeNoChangeListener.h"

void VeNoChangeListener::addListener (const std::string& name, VeNoListener* listener)
{
    if (!hasListener (name))
    {
        m_listener[name] = listener;
    }
}

void VeNoChangeListener::removeListener (const std::string& name)
{
    if (hasListener (name))
    {
        m_listener.erase (name);
    }
}

void VeNoChangeListener::notifyListener (const std::string& name, float value)
{
    if (hasListener (name) && m_listener[name] != nullptr)
    {
        m_listener[name]->notify (name, value);
    }
}

bool VeNoChangeListener::hasListener (const std::string& name)
{
    return m_listener.find (name) != m_listener.end ();
}

void VeNoChangeListener::notifyParameterChanged (const std::string& name, VeNoParameter* parameter)
{
    if (hasListener (name) && m_listener[name] != nullptr)
    {
        m_listener[name]->parameterChanged (parameter);
    }
}
