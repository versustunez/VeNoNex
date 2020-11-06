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
    if (!m_modulators.contains (name))
    {
        auto source = new VeNoMatrixSource();
        m_modulators[name] = source;
        m_rawOrder.push_back (source);
        source->name = name;
        source->showName = modulator->m_showName;
    }
    m_modulators[name]->sources.push_back (modulator);
}

//matrix is not in the valueTree-state is some own implementation!
void VeNoMatrix::updateSlots ()
{
    std::lock_guard<std::mutex> l (_mtx);
    for (auto& m_source : m_rawOrder)
    {
        for (auto& source : m_source->sources)
        {
            source->update ();
        }
    }

    for (auto& value : m_rawMods)
    {
        value->resetMatrixPos ();
    }

    for (auto& m_slot : m_slots)
    {
        auto slotSource = m_slot.second->modulator;
        auto value = m_slot.second->value;
        auto amount = m_slot.second->amount;
        for (auto& source : slotSource->sources)
        {
            auto valueToAdd = source->m_value * amount;

            for (auto& item : value)
            {
                if (source->m_voice != -1)
                {
                    item->addValueForVoice (valueToAdd, source->m_voice);
                }
                else
                {
                    item->addValue (valueToAdd);
                }
            }
        }
    }
}

bool VeNoMatrix::setMatrixModulation (const std::string& name, const std::string& source, double amount)
{
    std::lock_guard<std::mutex> l (_mtx);
    auto c = std::string (source + name);
    if (m_slots.find (c) == m_slots.end ())
    {
        bool isAll = name == "osc_all_pitch";
        if (isAll || m_values.contains (name))
        {
            m_slots[c] = new VeNoMatrixTarget ();
            auto* slot = m_slots[c];
            slot->source = source;
            slot->name = name;
            slot->amount = amount;
            slot->modulator = m_modulators[source];
            if (!isAll)
            {
                slot->value.push_back (m_values[name]);
            }
            else
            {
                slot->value.push_back (m_values["osc1__cents"]);
                slot->value.push_back (m_values["osc2__cents"]);
                slot->value.push_back (m_values["osc3__cents"]);
                slot->value.push_back (m_values["osc4__cents"]);
            }
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
    clear ();
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

const tsl::robin_map<std::string, VeNoMatrixSource*>& VeNoMatrix::getModulators ()
{
    return m_modulators;
}

tsl::robin_map<std::string, VeNoMatrixTarget*>& VeNoMatrix::getSlots ()
{
    return m_slots;
}

std::string VeNoMatrix::getModulatorNameFromSlot (const std::string& key)
{
    return m_slots[key]->modulator->showName;
}

void VeNoMatrix::removeSlot (const std::string& key)
{
    std::lock_guard<std::mutex> l (_mtx);
    if (m_slots.find (key) != m_slots.end ())
    {
        auto element = m_slots[key];
        for (auto& i : element->value)
        {
            i->resetMatrixPos ();
            i->addValue (0);
        }
        delete m_slots[key];
        m_slots.erase (key);
    }
}

void VeNoMatrix::addModValue (const std::string& name, ModulateValue* value)
{
    m_values[name] = value;
    m_rawMods.push_back(value);
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
