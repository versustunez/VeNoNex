#include "VeNoParameter.h"
#include "../../VenoInstance.h"

VeNoParameter::VeNoParameter (const std::string& name, const std::string& shownName, double min, double max, double value,
                              const std::string& id) :
                              m_name(name), m_showName(shownName), m_id(id), m_max(max), m_min(min), m_value(value)
{
}

VeNoParameter::~VeNoParameter ()
{
    m_modulateValue.reset ();
}

void VeNoParameter::createModulationValue ()
{
    m_modulateValue = std::make_unique<ModulateValue> (m_name, m_id);
    VenoInstance::getInstance(m_id)->matrix->addModValue(m_name, m_modulateValue.get());
    m_modulateValue->set (m_value, m_max, m_min);
    m_modulateValue->resetMatrixPos();
    m_isModulation = true;
}

void VeNoParameter::setValue (double value)
{
    m_value = value;
    if (m_isModulation)
    {
        m_modulateValue->setBaseValue (m_value);
    }
}

double VeNoParameter::getValue ()
{
    if (m_isModulation)
    {
        return m_modulateValue->getValue ();
    }
    return m_value;
}

std::string VeNoParameter::getShowName ()
{
    return m_showName;
}

std::unique_ptr<RangedAudioParameter> VeNoParameter::createParameter (ParameterTypes type)
{
    switch (type)
    {
        case Integer:
            return std::make_unique<AudioParameterInt> (m_name, m_showName, m_min, m_max, m_value);
        case Float:
            return std::make_unique<AudioParameterFloat> (m_name, m_showName, m_min, m_max, m_value);
        case Boolean:
            return std::make_unique<AudioParameterBool> (m_name, m_showName, m_value == 1);
        default:
            return std::make_unique<AudioParameterFloat> (m_name, m_showName, m_min, m_max, m_value);
    }
}

bool VeNoParameter::getAsBoolean ()
{
    return m_value > 0.5;
}

int VeNoParameter::getAsInt ()
{
    return (int) getValue ();
}

double VeNoParameter::getBaseValue ()
{
    return m_value;
}

double VeNoParameter::getValueForVoice (int voice)
{
    if (m_isModulation && voice != -1)
    {
        return m_modulateValue->getValueForVoice (voice);
    }
    return m_value;
}

std::shared_ptr<ModulateValue> VeNoParameter::getModulateValue ()
{
    return m_modulateValue;
}

double VeNoParameter::getMaxValue () const
{
    return m_max;
}

double VeNoParameter::getMinValue () const
{
    return m_max;
}