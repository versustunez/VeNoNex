#include "VeNoEnvelope.h"
#include "../../VenoInstance.h"

VeNoEnvelope::VeNoEnvelope (const std::string& id, const std::string& name, double sampleRate)
{
    m_id = id;
    m_name = name;
    m_handler = VenoInstance::getInstance (id)->handler;
    if (sampleRate > 0)
    {
        m_sampleRate = sampleRate;
        setSampleRate (m_sampleRate);
    }
    VenoInstance::getInstance (m_id)->matrix->addModulator (name, this);
    m_release = m_handler->getParameter (m_name + "__release");
    m_sustain = m_handler->getParameter (m_name + "__sustain");
    m_decay = m_handler->getParameter (m_name + "__decay");
    m_attack = m_handler->getParameter (m_name + "__attack");
}

float VeNoEnvelope::getValue ()
{
    return m_value;
}

bool VeNoEnvelope::isActive ()
{
    return m_adsr.isActive ();
}

void VeNoEnvelope::noteOn ()
{
    m_adsr.noteOn ();
}

void VeNoEnvelope::noteOff ()
{
    m_adsr.noteOff ();
}

void VeNoEnvelope::setSampleRate (float sampleRate)
{
    VeNoEnvelope::m_sampleRate = sampleRate;
    m_adsr = ADSR ();
    m_adsr.setSampleRate (m_sampleRate);
    m_adsr.setParameters (m_parameters);
    m_adsr.reset ();
}

void VeNoEnvelope::update ()
{
    m_value = m_adsr.getNextSample ();
}

void VeNoEnvelope::prepare ()
{
    m_parameters.release = m_release->getValue ();
    m_parameters.sustain = m_sustain->getValue ();
    m_parameters.decay = m_decay->getValue ();
    m_parameters.attack = m_attack->getValue ();
    m_adsr.setParameters (m_parameters);
}
