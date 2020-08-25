#include "SynthOscillator.h"

SynthOscillator::SynthOscillator (const std::string& id, int maxVoices, const std::string& name)
        : BaseOscillator (id, name, maxVoices)
{
}

SynthOscillator::~SynthOscillator ()
{
    BaseOscillator::~BaseOscillator ();
}

float SynthOscillator::getValue ()
{
    return getMonoValue ();
}

void SynthOscillator::update ()
{

}
