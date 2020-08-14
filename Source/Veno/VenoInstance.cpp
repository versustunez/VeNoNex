//
// Created by versustune on 09.06.20.
//

#include "VenoInstance.h"
#include <utility>
#include "Utils/Logger.h"

std::unordered_map<std::string, std::shared_ptr<VenoInstance>> VenoInstance::instances;

VenoInstance::VenoInstance(std::string id)
{
    m_id = std::move(id);
    m_synthInstance = std::make_shared<SynthInstance>(id);
    audioBuffer = std::make_shared<VenoBuffer>();
    state = new VeNoState(m_id);
    matrix = new VeNoMatrix(m_id);
    handler = new ParameterHandler(m_id);
}

VenoInstance::~VenoInstance()
{
    m_synthInstance.reset();
    audioBuffer.reset();
    delete state;
    delete matrix;
    delete handler;
}

std::shared_ptr<VenoInstance> VenoInstance::createInstance(const std::string& id)
{
    if (hasInstance(id))
    {
        return getInstance(id);
    }
    auto instance = std::make_shared<VenoInstance>(id);
    instances.insert(std::pair<std::string, std::shared_ptr<VenoInstance>>(id, instance));
    DBG("Created VenoInstance with id: " + id);
    return instance;
}

// will return the instance or a empty new on... can find out because the id is fucked!
std::shared_ptr<VenoInstance> VenoInstance::getInstance(const std::string& id)
{
    if (hasInstance(id))
    {
        return instances[id];
    }
    return createInstance(id);
}

const std::shared_ptr<SynthInstance>& VenoInstance::getSynthInstance() const
{
    return m_synthInstance;
}

void VenoInstance::deleteInstance(const std::string& processId)
{
    if (hasInstance(processId))
    {
        instances[processId].reset();
        instances.erase(processId);
        VeNo::Logger::debugMessage("Removed VenoInstance with id: " + processId);
    }
}

std::unordered_map<std::string, std::shared_ptr<VenoInstance>> VenoInstance::getAll()
{
    return instances;
}

bool VenoInstance::hasInstance(const std::string& id)
{
    return instances.find(id) != instances.end();
}
