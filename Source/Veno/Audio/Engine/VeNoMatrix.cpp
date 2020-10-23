#include "VeNoMatrix.h"
#include "../../Utils/StringUtils.h"
#include "../../VenoInstance.h"

VeNoMatrix::VeNoMatrix (const std::string& processId) : m_processId (processId)
{
    DBG("Create Matrix with ID: " + processId);
}

VeNoMatrix::~VeNoMatrix ()
{
    DBG("Destroy Matrix!");
    for (auto& m_slot : m_slots)
    {
        delete m_slot.second;
    }

    m_slots.clear ();
    m_modulators.clear ();
    m_values.clear ();
}

void VeNoMatrix::removeModulator (const std::string& name)
{
    m_modulators.erase (name);
}


void VeNoMatrix::addModulator (const std::string& name, Modulator* modulator)
{
    m_rawOrder.push_back (name);
    m_modulators.emplace (std::pair<const std::string&, Modulator*> (name, modulator));
}

//matrix is not in the valueTree-state is some own implementation!
void VeNoMatrix::updateSlots ()
{
    std::lock_guard<std::mutex> l (_mtx);
    auto instance = VenoInstance::getInstance (m_processId);
    for (auto& m_source : m_modulators)
    {
        m_source.second->update ();
    }

    for (auto& value : m_values)
    {
        value.second->resetMatrixPos ();
    }

    for (auto& m_slot : m_slots)
    {
        auto source = m_modulators[m_slot.second->source];
        auto value = m_slot.second->value;
        if (value == nullptr || source == nullptr)
            continue;
        auto amount = m_slot.second->amount;
        auto valueToAdd = source->getValue () * amount;
        if (source->m_voice != -1)
        {
            value->addValueForVoice (valueToAdd, source->getVoice ());
        }
        else
        {
            value->addValue (valueToAdd);
        }
    }
    if (instance->glContext != nullptr)
    {
        instance->glContext->triggerRepaint ();
    }
}

bool VeNoMatrix::setMatrixModulation (const std::string& name, const std::string& source, double amount)
{
    auto c = std::string (source + name);
    if (m_slots.find (c) == m_slots.end ())
    {
        auto val = VenoInstance::getInstance (m_processId)->handler->getModulateValue (name);
        if (val != nullptr)
        {
            m_slots[c] = new VeNoMatrixTarget ();
            m_slots[c]->source = source;
            m_slots[c]->name = name;
            m_slots[c]->amount = amount;
            m_slots[c]->value = VenoInstance::getInstance (m_processId)->handler->getModulateValue (name);
            return true;
        }
        return false;
    }
    return false;
}

XmlElement* VeNoMatrix::saveMatrixToXML ()
{
    std::lock_guard<std::mutex> l (_mtx);
    if (m_slots.empty ())
    {
        return nullptr;
    }
    auto xml = new XmlElement ("Matrix");
    for (auto& m_slot : m_slots)
    {
        auto subXml = new XmlElement ("Matrix-Item");
        std::string name = m_slot.second->source + m_slot.second->name;
        subXml->setAttribute(Identifier("source"), String(m_slot.second->source));
        subXml->setAttribute(Identifier("name"), String(m_slot.second->name));
        subXml->setAttribute(Identifier("amount"), String(m_slot.second->amount));
        xml->addChildElement (subXml);
    }
    return xml;
}

void VeNoMatrix::getMatrixFromXML (XmlElement* xml)
{
    std::lock_guard<std::mutex> l (_mtx);
    // first we need to delete the state!
    for (auto& m_slot : m_slots)
    {
        delete m_slot.second;
    }
    m_slots.clear ();
    // recreate the matrix from xml...
    for (int i = 0; i < xml->getNumChildElements(); ++i)
    {
        auto item = xml->getChildElement(i);
        auto src = item->getStringAttribute("source").toStdString();
        auto name = item->getStringAttribute("name").toStdString();
        auto amount = item->getDoubleAttribute("amount");
        setMatrixModulation(name, src, amount);
    }
}

void VeNoMatrix::setMatrixModulationValue (const std::string& key, double amount)
{
    std::lock_guard<std::mutex> l (_mtx);
    if (m_slots.find (key) != m_slots.end ())
    {
        m_slots[key]->amount = amount;
    }
}

const tsl::robin_map<std::string, Modulator*>& VeNoMatrix::getModulators ()
{
    return m_modulators;
}

tsl::robin_map<std::string, VeNoMatrixTarget*>& VeNoMatrix::getSlots ()
{
    return m_slots;
}

std::string VeNoMatrix::getModulatorNameFromSlot (const std::string& key)
{
    return m_modulators[m_slots[key]->source]->m_showName;
}

void VeNoMatrix::removeSlot (const std::string& key)
{
    std::lock_guard<std::mutex> l (_mtx);
    if (m_slots.find (key) != m_slots.end ())
    {
        delete m_slots[key];
        m_slots.erase (key);
    }
}

void VeNoMatrix::addModValue (const std::string& name, ModulateValue* value)
{
    m_values[name] = value;
}

void VeNoMatrix::clear ()
{
    std::lock_guard<std::mutex> l (_mtx);
    // first we need to delete the state!
    for (auto& m_slot : m_slots)
    {
        delete m_slot.second;
    }
    m_slots.clear ();
}
