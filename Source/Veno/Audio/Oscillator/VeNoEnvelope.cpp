#include "VeNoEnvelope.h"
#include "../../VenoInstance.h"

VeNoEnvelope::VeNoEnvelope (const std::string& id, const std::string& name, double sampleRate)
:m_id(id), m_name(name), m_handler(VenoInstance::getInstance (m_id)->handler)
{
    if (sampleRate > 0)
    {
        m_sampleRate = sampleRate;
        setSampleRate (m_sampleRate);
    }
    if (m_name == "env1")
    {
        this->m_showName = "Envelope (Voices)";
    }
    else if (m_name == "env2")
    {
        this->m_showName = "Envelope (Free)";
    }
    else
    {
        this->m_showName = "Envelope (" + m_name + ")";
    }
    VenoInstance::getInstance (m_id)->matrix->addModulator (name + "_env", this);
    m_release = m_handler->getParameter (m_name + "__release");
    m_sustain = m_handler->getParameter (m_name + "__sustain");
    m_decay = m_handler->getParameter (m_name + "__decay");
    m_attack = m_handler->getParameter (m_name + "__attack");
}

double VeNoEnvelope::getValue ()
{
    return m_value;
}

bool VeNoEnvelope::isActive ()
{
    return m_adsr.isActive ();
}

void VeNoEnvelope::noteOn ()
{
    prepare ();
    m_adsr.noteOn ();
}

void VeNoEnvelope::noteOff ()
{
    m_adsr.noteOff ();
}

void VeNoEnvelope::setSampleRate (double sampleRate)
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
    float release = m_release->m_value / 1000;
    float attack = m_attack->m_value / 1000;
    float decay = m_decay->m_value / 1000;
    if (m_parameters.release != release || m_parameters.sustain != m_sustain->m_value
        || m_parameters.attack != attack || m_parameters.decay != decay)
    {
        m_parameters.release = release;
        m_parameters.sustain = m_sustain->m_value;
        m_parameters.decay = decay;
        m_parameters.attack = attack;
        m_adsr.setParameters (m_parameters);
    }
}
