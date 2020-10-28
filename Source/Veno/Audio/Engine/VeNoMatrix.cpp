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
        m_rawOrder.push_back (name);
        m_modulators[name] = new VeNoMatrixSource ();
        m_modulators[name]->name = name;
        m_modulators[name]->showName = modulator->m_showName;
    }
    m_modulators[name]->sources.push_back (modulator);
}

//matrix is not in the valueTree-state is some own implementation!
void VeNoMatrix::updateSlots ()
{
    std::lock_guard<std::mutex> l (_mtx);
    auto instance = VenoInstance::getInstance (m_processId);
    for (auto& m_source : m_modulators)
    {
        for (auto& source : m_source.second->sources)
        {
            source->update ();
        }
    }

    for (auto& value : m_values)
    {
        value.second->resetMatrixPos ();
    }

    for (auto& m_slot : m_slots)
    {
        if (m_slot.second == nullptr)
            continue;
        auto slotSource = m_modulators[m_slot.second->source];
        auto value = m_slot.second->value;
        if (slotSource == nullptr)
            continue;

        for (auto& source : slotSource->sources)
        {
            auto amount = m_slot.second->amount;
            auto valueToAdd = source->getValue () * amount;

            for (auto& item : value)
            {
                if (item == nullptr)
                    continue;

                if (source->m_voice != -1)
                {
                    item->addValueForVoice (valueToAdd, source->getVoice ());
                }
                else
                {
                    item->addValue (valueToAdd);
                }
            }
        }
    }
    if (instance->glContext != nullptr)
    {
        instance->glContext->triggerRepaint ();
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
    return m_modulators[m_slots[key]->source]->showName;
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
