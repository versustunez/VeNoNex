#include "VeNoXDetune.h"
#include "../../../../Utils.h"
#include "../../../../Utils/VeNoParameterStringHelper.h"

void VeNoXDetune::prepareDetune(int voices)
{
    float detune = m_parameters->m_detuneDense->getValue();
    if (m_lookup.empty() || voices != m_lastVoices || m_lastDetune != detune)
    {
        m_lastDetune = detune;
        if (m_lastDetune != detune)
        {
            getRealDetune();
        }
        m_lookup[0] = 1;

        if (voices == 1) {
            return;
        }

        float split = detune / (voices - 1);
        float cents = 0;
        for (int i = 1; i < voices; ++i)
        {
            cents += split;
            float plus;
            if ((i & 1) == 1)
            {
                plus = VeNo::Utils::centsToRatio(-cents);
            }
            else
            {
                plus = VeNo::Utils::centsToRatio(cents);
            }
            m_lookup[i] = plus;
        }
    }
    m_lastVoices = voices;
}

void VeNoXDetune::getRealDetune()
{
    float d = m_lastDetune / m_detuneCents;
    m_currentDetune = std::atan(d * d * d * d) * m_detuneCents;
}
VeNoXDetune::VeNoXDetune(int maxSize, std::shared_ptr<OscillatorParameters>& parameters, const std::string& name)
        : DetuneLookup(maxSize, parameters, name)
{

}
