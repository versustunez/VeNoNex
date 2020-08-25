#include "VenoEnvelope.h"
#include "cmath"
#include "../../VenoInstance.h"
#include "../../Utils/VeNoParameterStringHelper.h"

VenoEnvelope::VenoEnvelope(const std::string& id, const std::string& name, double sampleRate)
{
    m_id = id;
    m_name = name;
    m_handler = VenoInstance::getInstance(id)->handler;
    if (sampleRate > 0)
    {
        m_sampleRate = sampleRate;
        setSampleRate(m_sampleRate);
    }
}

float VenoEnvelope::getValue()
{
    return m_value;
}

bool VenoEnvelope::isActive()
{
    return m_adsr.isActive();
}

void VenoEnvelope::noteOn()
{
    m_adsr.noteOn();
}

void VenoEnvelope::noteOff()
{
    m_adsr.noteOff();
}

void VenoEnvelope::setSampleRate(float sampleRate)
{
    VenoEnvelope::m_sampleRate = sampleRate;
    m_adsr = ADSR();
    m_adsr.setSampleRate(m_sampleRate);
    m_adsr.setParameters(m_parameters);
    m_adsr.reset();
}

void VenoEnvelope::update()
{
    m_value = m_adsr.getNextSample();
}

void VenoEnvelope::prepare()
{
    m_parameters.release = m_handler->getParameterValue(VeNoParameterStringHelper::getForOscillator(m_name, 15));
    m_parameters.sustain = m_handler->getParameterValue(VeNoParameterStringHelper::getForOscillator(m_name, 14));
    m_parameters.decay = m_handler->getParameterValue(VeNoParameterStringHelper::getForOscillator(m_name, 13));
    m_parameters.attack = m_handler->getParameterValue(VeNoParameterStringHelper::getForOscillator(m_name, 12));
    m_adsr.setParameters(m_parameters);
}
