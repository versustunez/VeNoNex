#include "SynthOscillator.h"

SynthOscillator::SynthOscillator (const std::string& id, int maxVoices, const std::string& name)
        : BaseOscillator (id, name, maxVoices)
{
}

SynthOscillator::~SynthOscillator ()
{
    BaseOscillator::~BaseOscillator ();
}

double SynthOscillator::getValue ()
{
    return getMonoValue ();
}

void SynthOscillator::update ()
{

}

bool SynthOscillator::render ()
{
    int voices = m_parameters->m_voices->getAsInt ();
    if (m_midiNote == 0 || voices == 0 || !m_parameters->m_active->getAsBoolean ())
        return false;
    setFrequency ();
    if (!preProcessing () || !BaseOscillator::render () || !postProcessing ())
        return false;
    return true;
}
