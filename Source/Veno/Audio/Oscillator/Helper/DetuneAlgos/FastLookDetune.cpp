#include "FastLookDetune.h"
#include "../../../../Utils.h"

void FastLookDetune::prepareDetune (int voices)
{
    double detune = m_parameters->m_detuneDense->getValueForVoice (m_parameters->m_index);
    if (!isInit || voices != m_lastVoices || m_lastDetune != detune)
    {
        if (voices == 1)
            return;
        isInit = true;
        m_lastDetune = detune;
        m_currentDetune = detune;
        m_lookup[0] = 1;
        for (int i = 1; i < voices; ++i)
        {
            double plus;
            if ((i & 1) == 1)
                plus = VeNo::Utils::centsToRatio (-(m_currentDetune / i));
            else
                plus = VeNo::Utils::centsToRatio ((m_currentDetune / i));
            m_lookup[i] = plus;
        }
    }
    m_lastVoices = voices;
}

FastLookDetune::FastLookDetune (int maxSize, std::shared_ptr<OscillatorParameters>& parameters, const std::string& name)
        : DetuneLookup (maxSize, parameters, name)
{

}
