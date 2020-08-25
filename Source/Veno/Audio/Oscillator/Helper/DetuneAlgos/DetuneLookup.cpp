#include "DetuneLookup.h"

DetuneLookup::DetuneLookup (int maxSize, std::shared_ptr<OscillatorParameters>& parameters, const std::string& name)
{
    m_size = maxSize;
    m_parameters = parameters;
    m_lookup.resize (maxSize);
    m_name = name;
}

float DetuneLookup::getDetuneFreq (int index)
{
    return m_frequency * m_lookup[index];
}

void DetuneLookup::setFrequency (float frequency, int midiNote)
{
    m_frequency = frequency;
    m_midiNote = midiNote;
}
