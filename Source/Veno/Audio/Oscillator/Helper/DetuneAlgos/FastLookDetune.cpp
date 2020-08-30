#include "FastLookDetune.h"
#include "../../../../Utils.h"

void FastLookDetune::prepareDetune (int voices)
{
    float detune = m_parameters->m_detuneDense->getValueForVoice (m_parameters->m_index);
    if (m_lookup.empty () || voices != m_lastVoices || m_lastDetune != detune)
    {
        m_lastDetune = detune;
        m_currentDetune = detune;
        m_lookup[0] = 1;
        float split = detune / (voices - 1);
        float cents = 0;
        for (int i = 1; i < m_size; ++i)
        {
            float plus;
            if ((i & 1) == 1)
            {
                plus = VeNo::Utils::centsToRatio (-cents);
            }
            else
            {
                plus = VeNo::Utils::centsToRatio (cents);
            }
            cents += split;
            m_lookup[i] = plus;
        }
    }
    m_lastVoices = voices;
}

FastLookDetune::FastLookDetune (int maxSize, std::shared_ptr<OscillatorParameters>& parameters, const std::string& name)
        : DetuneLookup (maxSize, parameters, name)
{

}
