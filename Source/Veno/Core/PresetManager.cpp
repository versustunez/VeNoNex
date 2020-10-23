#include "PresetManager.h"
#include "../VenoInstance.h"

PresetManager::PresetManager (const std::string& pid)
        : m_pid (pid)
{

}

PresetManager::~PresetManager ()
{

}

void PresetManager::save ()
{

}

void PresetManager::load ()
{

}

void PresetManager::setName (const std::string& name)
{
    m_name = name;
}

void PresetManager::loadNext ()
{

}

void PresetManager::loadPrev ()
{

}

std::unique_ptr<XmlElement> PresetManager::getCurrentData ()
{
    auto instance = VenoInstance::getInstance (m_pid);
    auto state = instance->treeState->copyState ();
    auto preset = new XmlElement ("VeNoPreset");
    preset->setAttribute ("presetName", m_name);
    auto params = new XmlElement (*state.createXml ());
    preset->addChildElement (params);
    auto matrixXML = instance->matrix->saveMatrixToXML ();
    if (matrixXML != nullptr)
    {
        preset->addChildElement (matrixXML);
    }
    auto xml = std::make_unique<XmlElement> (*preset);
    delete preset;
    return xml;
}

void PresetManager::setCurrentData (const std::unique_ptr<XmlElement>& data)
{
    auto instance = VenoInstance::getInstance (m_pid);
    auto treeState = instance->treeState;
    auto params = data->getChildByName (treeState->state.getType ());
    if (params != nullptr)
    {
        treeState->replaceState (ValueTree::fromXml (*params));
    }
    auto matrix = data->getChildByName ("Matrix");
    if (matrix != nullptr)
    {
        instance->matrix->getMatrixFromXML (matrix);
    }
    instance->presetManager->setName (data->getStringAttribute ("presetName").toStdString ());
    instance->changeListener->notifyListener ("presetEditor", 1.0);
}

// reset Plugin to Init State...
void PresetManager::toInit ()
{

}
