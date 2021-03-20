#include "DetuneHelper.h"
#include "DetuneAlgos/VeNoXDetune.h"
#include "DetuneAlgos/SuperDetune.h"
#include "DetuneAlgos/FastLookDetune.h"

DetuneHelper::DetuneHelper (const std::string& name, std::shared_ptr<OscillatorParameters>& parameters, int voiceCount)
        : m_name (name), m_parameters (parameters)
{
    m_detuneAlgos[0] = new VeNoXDetune (voiceCount, parameters, name);
    m_detuneAlgos[1] = new FastLookDetune (voiceCount, parameters, name);
    m_detuneAlgos[2] = new SuperDetune (voiceCount, parameters, name);
}

DetuneHelper::~DetuneHelper ()
{
    for (auto& m_detuneAlgo : m_detuneAlgos)
        delete m_detuneAlgo;
}

DetuneLookup* DetuneHelper::getDetune ()
{
    return m_detuneAlgos[m_mode];
}

void DetuneHelper::setMode ()
{
    m_mode = (int) m_parameters->m_detuneMode->getValue () - 1;
}

void DetuneHelper::update (double freq, int midiNote)
{
    m_mode = (int) m_parameters->m_detuneMode->getValue () - 1;
    int voices = m_parameters->m_voices->m_value;
    m_detuneAlgos[m_mode]->setFrequency (freq, midiNote);
    m_detuneAlgos[m_mode]->prepareDetune (voices);
}
