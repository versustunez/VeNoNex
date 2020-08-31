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
}

void VeNoMatrix::removeModulator (const std::string& name)
{
    m_modulators.erase (name);
}


void VeNoMatrix::addModulator (const std::string& name, Modulator* modulator)
{
    m_modulators.emplace (std::pair<const std::string&, Modulator*> (name, modulator));
}

//matrix is not in the valueTree-state is some own implementation!
void VeNoMatrix::updateSlots ()
{
    ParameterHandler* handler = VenoInstance::getInstance (m_processId)->handler;
    for (auto& m_source : m_modulators)
    {
        m_source.second->update ();
    }

    for (auto& m_slot : m_slots)
    {
        auto source = m_modulators[m_slot.second->source];
        auto value = handler->getModulateValue (m_slot.second->name);
        if (value == nullptr || source == nullptr)
            continue;
        auto amount = m_slot.second->amount;
        auto valueToAdd = source->getValue () * amount;
        if (source->getVoice () != -1)
        {
            value->addValueForVoice (valueToAdd, source->getVoice ());
        }
        else
        {
            value->addValue (source->getValue () * amount);
        }
    }
}

void VeNoMatrix::setMatrixModulation (const std::string& name, const std::string& source, double amount)
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
    }
    m_slots.clear ();
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
