#include "ModulateValue.h"
#include "../../Utils.h"

ModulateValue::ModulateValue (const std::string& name, const std::string& processId)
{
    m_name = name;
    m_processId = processId;
    m_voiceValues.resize (5);
}

void ModulateValue::addValue (float d)
{
    m_value += m_baseValue * d;
    m_value = VeNo::Utils::clamp (m_value, m_maxValue, m_minValue);
    for (int i = 0; i < 5; ++i)
    {
        addValueForVoice(d, i);
    }
}

ModulateValue::~ModulateValue () = default;

void ModulateValue::set (float value, float max, float min)
{
    m_baseValue = value;
    m_value = value;
    m_maxValue = max;
    m_minValue = min;
    for (int i = 0; i < 5; ++i)
    {
        m_voiceValues[i] = value;
    }
}

void ModulateValue::setBaseValue (float d)
{
    m_baseValue = d;
    m_value = d;
    for (int i = 0; i < 5; ++i)
    {
        m_voiceValues[i] = d;
    }
}

float ModulateValue::getValue ()
{
    return m_value;
}

void ModulateValue::addValueForVoice (float value, int voice)
{
    m_voiceValues[voice] = m_baseValue * value;
    m_voiceValues[voice] = VeNo::Utils::clamp (m_voiceValues[voice], m_maxValue, m_minValue);
}

float ModulateValue::getValueForVoice (int i)
{
    return m_voiceValues[i];
}
