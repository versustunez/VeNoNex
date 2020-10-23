#include "ModulateValue.h"
#include "../../Utils.h"
#include "../../VenoInstance.h"

ModulateValue::ModulateValue (const std::string& name, const std::string& processId)
        : m_name (name), m_processId (processId)
{
    m_voiceValues.resize (5);
    m_voiceMatrix.resize (5);
}

void ModulateValue::addValue (double d)
{
    m_matrixPos += d;
    m_value = m_matrixPos * (m_maxValue - m_minValue) + m_minValue;
    m_value = VeNo::Utils::clamp (m_value, m_minValue, m_maxValue);
    for (int i = 0; i < 5; ++i)
    {
        addValueForVoice(d, i);
    }
}

ModulateValue::~ModulateValue () = default;

void ModulateValue::set (double value, double max, double min)
{
    m_baseValue = value;
    m_value = value;
    m_maxValue = max;
    m_minValue = min;
    m_normalised = (value - m_minValue) / (m_maxValue - m_minValue);
    for (int i = 0; i < 5; ++i)
    {
        m_voiceValues[i] = value;
    }
}

void ModulateValue::setBaseValue (double d)
{
    m_normalised = (d - m_minValue) / (m_maxValue - m_minValue);
    m_baseValue = d;
    m_value = d;
    for (int i = 0; i < 5; ++i)
    {
        m_voiceValues[i] = d;
    }
}

double ModulateValue::getValue ()
{
    return m_value;
}

void ModulateValue::addValueForVoice (double value, int voice)
{
    m_voiceMatrix[voice] += value;
    m_voiceValues[voice] = m_voiceMatrix[voice] * (m_maxValue - m_minValue) + m_minValue;
    m_voiceValues[voice] = VeNo::Utils::clamp (m_voiceValues[voice], m_minValue, m_maxValue);
}

double ModulateValue::getValueForVoice (int i)
{
    return m_voiceValues[i];
}

void ModulateValue::resetMatrixPos ()
{
    m_matrixPosPrev = m_matrixPos;
    m_matrixPos = m_normalised;
    for (int i = 0; i < 5; ++i)
    {
        m_voiceMatrix[i] = m_normalised;
    }
}
