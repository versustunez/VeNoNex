//
// Created by versustune on 13.06.20.
//

#include "VeNoMatrix.h"
#include "../../Utils/StringUtils.h"

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
        m_slots.erase (m_slot.first);
    }

    for (auto& value : m_modulationValues)
    {
        delete value.second;
        m_modulationValues.erase (value.first);
    }

    for (auto& value : m_modulators)
    {
        delete value.second;
        m_modulators.erase (value.first);
    }
}

void VeNoMatrix::removeModulateValue (const std::string& name)
{
    m_modulationValues.erase (name);
}

void VeNoMatrix::removeModulator (const std::string& name)
{
    m_modulators.erase (name);
}

void VeNoMatrix::addModulateValue (const std::string& name, ModulateValue* modulateValue)
{
    m_modulationValues.emplace (std::pair<const std::string&, ModulateValue*> (name, modulateValue));
}

void VeNoMatrix::addModulator (const std::string& name, Modulator* modulator)
{
    m_modulators.emplace (std::pair<const std::string&, Modulator*> (name, modulator));
}

//matrix is not in the valueTree-state is some own implementation!
void VeNoMatrix::updateSlots ()
{
    for (auto& m_source : m_modulators)
    {
        m_source.second->update ();
    }

    for (auto& m_slot : m_slots)
    {
        auto source = m_modulators[m_slot.second->source];
        auto value = m_modulationValues[m_slot.second->name];
        auto amount = m_slot.second->amount;
        value->addValue (source->getValue () * amount);
    }
}
void VeNoMatrix::setMatrixModulation (const std::string& name, const std::string& source, float amount)
{
    auto c = std::string (source + name);
    if (m_slots.find (c) == m_slots.end ())
    {
        m_slots[c] = new VeNoMatrixTarget ();
        m_slots[c]->source = source;
        m_slots[c]->name = name;
    }
    m_slots[c]->amount = amount;
}

std::unique_ptr<XmlElement> VeNoMatrix::saveMatrixToXML ()
{
    auto* tree = new ValueTree ();
    for (auto& m_slot : m_slots)
    {
        std::string name = m_slot.second->source + m_slot.second->name;
        tree->setProperty (String (name), String (m_slot.second->toString ()), nullptr);
    }
    auto xml = tree->createXml ();
    delete tree;
    return xml;
}

void VeNoMatrix::getMatrixFromXML (std::unique_ptr<XmlElement>& xml)
{
    // first we need to delete the state!
    for (auto& m_slot : m_slots)
    {
        delete m_slot.second;
        m_slots.erase (m_slot.first);
    }
    // recreate the matrix from xml...
    auto tree = juce::ValueTree::fromXml (*xml);
    for (int i = 0; i < tree.getNumChildren (); ++i)
    {
        auto name = tree.getPropertyName (i);
        auto child = tree.getPropertyAsValue (name, nullptr);
        auto slot = VeNoMatrixTarget::fromString (child.toString ().toStdString ());
        if (slot != nullptr)
        {
            m_slots[name.toString ().toStdString ()] = slot;
        }
    }
}

// crate a string to save to ValueTree-State
std::string VeNoMatrixTarget::toString () const
{
    return std::string (source + "_#_" + name + "_#_" + std::to_string (amount));
}

// recreate from ValueTree-State... <3 is a very special format
VeNoMatrixTarget* VeNoMatrixTarget::fromString (const std::string& value)
{
    auto out = VeNo::StringUtils::split (value, "_#_");
    // if size is not 3 this is invalid! return nullptr!
    if (out.size () == 3)
    {
        auto returnValue = new VeNoMatrixTarget ();
        returnValue->source = out[0];
        returnValue->name = out[1];
        returnValue->amount = std::atof (out[2].c_str ());
        return new VeNoMatrixTarget ();
    }
    return nullptr;
}
