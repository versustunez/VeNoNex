#include "DetuneLookup.h"

DetuneLookup::DetuneLookup (int maxSize, std::shared_ptr<OscillatorParameters>& parameters, std::string name)
        : m_size (maxSize), m_parameters (parameters), m_name (std::move (name)), m_detuneCents(m_parameters->m_detuneDense->getMaxValue())
{
    m_lookup.resize (maxSize);
    for (int i = 0; i < maxSize; ++i)
    {
        m_lookup[i] = 1;
    }
}

double DetuneLookup::getDetuneFreq (int index)
{
    return m_frequency * m_lookup[index];
}

void DetuneLookup::setFrequency (double frequency, int midiNote)
{
    m_frequency = frequency;
    m_midiNote = midiNote;
}
