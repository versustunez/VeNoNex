#include "ParameterHandler.h"

ParameterHandler::ParameterHandler (const std::string& id)
        : m_id (id)
{
}

ParameterHandler::~ParameterHandler ()
{
    DBG("Deleting Parameter Handler");
    for (auto& listener : m_listener)
    {
        delete listener.second;
    }

    for (auto& parameter : m_parameters)
    {
        delete parameter.second;
    }
    m_params.clear ();
    m_parameters.clear ();
    m_listener.clear ();
}

void
ParameterHandler::addParameter (const std::string& name, const std::string& showName, double min, double max, double value,
                                ParameterTypes type)
{
    m_paramMaps.push_back(name);
    m_parameters[name] = new VeNoParameter (name, showName, min, max, value, m_id);
    m_params.push_back (m_parameters[name]->createParameter (type));
}


AudioProcessorValueTreeState::ParameterLayout ParameterHandler::setupProcessor ()
{
    if (m_params.empty ())
    {
        setupParameter ();
    }
    return {m_params.begin (), m_params.end ()};
}

void ParameterHandler::addParameterModulate (const std::string& name, const std::string& showName, double min, double max,
                                             double value, ParameterTypes type)
{
    addParameter (name, showName, min, max, value, type);
    // no support for Boolean Modulations!
    if (type == ParameterTypes::Boolean)
    {
        return;
    }
    m_parameters[name]->createModulationValue ();
}

void ParameterHandler::parameterChanged (const String& parameterID, float newValue)
{
    std::string value = parameterID.toStdString ();
    m_parameters[value]->setValue (newValue);
    for (const auto& element : m_listener)
    {
        element.second->parameterChanged (m_parameters[value]);
    }
}

void ParameterHandler::initParameterForListener (AudioProcessorValueTreeState* state)
{
    m_treeState = state;
    if (m_parameters.empty ())
    {
        DBG("NO PARAMS REGISTER");
    }
    for (auto& m_param : m_parameters)
    {
        state->addParameterListener (m_param.first, this);
    }
}

VeNoParameter* ParameterHandler::getParameter (const std::string& name)
{
    return m_parameters[name];
}

double ParameterHandler::getParameterValue (const std::string& name)
{
    return getParameterValue (name, 0);
}

double ParameterHandler::getParameterValue (const std::string& name, double defaultValue)
{
    auto param = m_parameters[name];
    if (param != nullptr)
    {
        return param->getValue ();
    }
    return defaultValue;
}

void ParameterHandler::setParameterValue (const std::string& parameterId, double value)
{
    if (m_parameters.find (parameterId) != m_parameters.end ())
    {
        return m_parameters[parameterId]->setValue (value);
    }
}

std::shared_ptr<ModulateValue> ParameterHandler::getModulateValue (const std::string& name)
{
    return m_parameters[name]->getModulateValue ();
}

void ParameterHandler::registerListener (const std::string& parameterId, VeNoListener* listener)
{
    m_listener[parameterId] = listener;
}

void ParameterHandler::unregisterListener (const std::string& parameterId)
{
    m_listener.erase (parameterId);
}

std::unordered_map<std::string, VeNoParameter*>& ParameterHandler::getParameters ()
{
    return m_parameters;
}

std::vector<std::string> ParameterHandler::rawParameters ()
{
    return m_paramMaps;
}
