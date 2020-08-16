//
// Created by versustune on 13.06.20.
//

#include "ModulateValue.h"

ModulateValue::ModulateValue(const std::string& name, const std::string& processId)
{
    m_name = name;
    m_processId = processId;
}

void ModulateValue::addValue(float d)
{
    m_value += d;
    if (m_value > m_maxValue)
    {
        m_value = m_maxValue;
    }
    if (m_value < m_minValue)
    {
        m_value = m_minValue;
    }
}

ModulateValue::~ModulateValue() = default;

void ModulateValue::set(float value, float max, float min)
{
    m_baseValue = value;
    m_value = value;
    m_maxValue = max;
    m_minValue = min;
}

void ModulateValue::setBaseValue(float d)
{
    m_baseValue = d;
}
