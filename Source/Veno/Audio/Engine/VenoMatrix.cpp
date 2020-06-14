//
// Created by versustune on 13.06.20.
//

#include "VenoMatrix.h"

VenoMatrix::VenoMatrix (const std::string& processId) : m_processId(processId)
{
    for (auto& m_slot : m_slots)
    {
        m_slot = new VenoMatrixSlot();
    }
}

VenoMatrix::~VenoMatrix ()
{
    for (auto& m_slot : m_slots)
    {
        delete m_slot;
    }
}

VenoMatrixSlot* VenoMatrix::getSlotById (int id)
{
    return m_slots[id];
}

void VenoMatrix::removeModulateValue (const std::string& name)
{
    m_modulationValues.erase(name);
}

void VenoMatrix::removeModulator (const std::string& name)
{
    m_modulators.erase(name);
}

void VenoMatrix::addModulateValue (const std::string& name, ModulateValue* modulateValue)
{
    m_modulationValues.emplace(std::pair<const std::string&, ModulateValue*>(name, modulateValue));
}

void VenoMatrix::addModulator (const std::string& name, Modulator* modulator)
{
    m_modulators.emplace(std::pair<const std::string&, Modulator*>(name, modulator));
}

void VenoMatrix::updateSlots ()
{
    for (auto& m_slot : m_slots)
    {
        if (m_slot->sourceName == "none")
        {
            continue;
        }
        if (m_modulators.find(m_slot->sourceName) != m_modulators.end())
        {
            auto modulator = m_modulators[m_slot->sourceName];
            if (modulator == nullptr)
            {
                continue;
            }
            modulator->update();
            for (auto& value : m_slot->targets)
            {
                if (value.name != "none")
                {
                    if (m_modulationValues.find(value.name) != m_modulationValues.end())
                    {
                        auto modValue = m_modulationValues[value.name];
                        if (modValue == nullptr)
                        {
                            continue;
                        }
                        modValue->addValue(modulator->getValue() * value.amount);
                    }
                }
            }
        }
    }
}