//
// Created by versustune on 28.09.19.
//

#include "VenoEnvelope.h"
#include "cmath"

VenoEnvelope::VenoEnvelope(double sampleRate)
{
    if (sampleRate > 0)
    {
        m_sampleRate = sampleRate;
        setSampleRate(m_sampleRate);
    }
}

void VenoEnvelope::setAttack(float attack)
{
    if (parameters.attack != attack)
    {
        parameters.attack = attack;
        adsr.setParameters(parameters);
    }
}

void VenoEnvelope::setRelease(float release)
{
    if (parameters.release != release)
    {
        parameters.release = release;
        adsr.setParameters(parameters);
    }
}

void VenoEnvelope::setSustain(float sustain)
{
    if (parameters.sustain != sustain)
    {
        parameters.sustain = sustain;
        adsr.setParameters(parameters);
    }
}

void VenoEnvelope::setDecay(float decay)
{
    if (parameters.decay != decay)
    {
        parameters.decay = decay;
        adsr.setParameters(parameters);
    }
}

float VenoEnvelope::getValue()
{
    return adsr.getNextSample();
}

bool VenoEnvelope::isActive()
{
    return adsr.isActive();
}

void VenoEnvelope::noteOn()
{
    if (reTrigger)
    {
        adsr.reset();
    }
    adsr.noteOn();
}

void VenoEnvelope::noteOff()
{
    adsr.noteOff();
}

void VenoEnvelope::setSampleRate(float sampleRate)
{
    VenoEnvelope::m_sampleRate = sampleRate;
    adsr = ADSR();
    adsr.setSampleRate(m_sampleRate);
    adsr.setParameters(parameters);
    adsr.reset();
}
