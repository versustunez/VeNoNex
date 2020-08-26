#include "VenoEnvelope.h"
#include "../../VenoInstance.h"
#include "../../Utils/VeNoParameterStringHelper.h"

VenoEnvelope::VenoEnvelope (const std::string& id, const std::string& name, double sampleRate)
{
    m_id = id;
    m_name = name;
    m_handler = VenoInstance::getInstance (id)->handler;
    if (sampleRate > 0)
    {
        m_sampleRate = sampleRate;
        setSampleRate (m_sampleRate);
    }
    VenoInstance::getInstance(m_id)->matrix->addModulator(name, this);
    m_release = m_handler->getParameter(VeNoParameterStringHelper::getForOscillator (m_name, 15));
    m_sustain = m_handler->getParameter (VeNoParameterStringHelper::getForOscillator (m_name, 14));
    m_decay = m_handler->getParameter (VeNoParameterStringHelper::getForOscillator (m_name, 13));
    m_attack = m_handler->getParameter (VeNoParameterStringHelper::getForOscillator (m_name, 12));
}

float VenoEnvelope::getValue ()
{
    return m_value;
}

bool VenoEnvelope::isActive ()
{
    return m_adsr.isActive ();
}

void VenoEnvelope::noteOn ()
{
    m_adsr.noteOn ();
}

void VenoEnvelope::noteOff ()
{
    m_adsr.noteOff ();
}

void VenoEnvelope::setSampleRate (float sampleRate)
{
    VenoEnvelope::m_sampleRate = sampleRate;
    m_adsr = ADSR ();
    m_adsr.setSampleRate (m_sampleRate);
    m_adsr.setParameters (m_parameters);
    m_adsr.reset ();
}

void VenoEnvelope::update ()
{
    m_value = m_adsr.getNextSample ();
}

void VenoEnvelope::prepare ()
{
    m_parameters.release = m_release->getValue();
    m_parameters.sustain = m_sustain->getValue();
    m_parameters.decay = m_decay->getValue();
    m_parameters.attack = m_attack->getValue();
    m_adsr.setParameters (m_parameters);
}
