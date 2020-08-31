#include "VeNoXDetune.h"
#include "../../../../Utils.h"

void VeNoXDetune::prepareDetune (int voices)
{
    double detune = m_parameters->m_detuneDense->getValueForVoice(m_parameters->m_index);
    if (m_lookup.empty () || voices != m_lastVoices || m_lastDetune != detune)
    {
        m_lastDetune = detune;
        if (m_lastDetune != detune)
        {
            getRealDetune ();
        }
        m_lookup[0] = 1;

        if (voices == 1)
        {
            return;
        }

        double split = detune / (voices - 1);
        double cents = 0;
        for (int i = 1; i < voices; ++i)
        {
            cents += split;
            double plus;
            if ((i & 1) == 1)
            {
                plus = VeNo::Utils::centsToRatio (-cents);
            }
            else
            {
                plus = VeNo::Utils::centsToRatio (cents);
            }
            m_lookup[i] = plus;
        }
    }
    m_lastVoices = voices;
}

void VeNoXDetune::getRealDetune ()
{
    double d = m_lastDetune / m_detuneCents;
    m_currentDetune = std::atan (d * d * d * d) * m_detuneCents;
}

VeNoXDetune::VeNoXDetune (int maxSize, std::shared_ptr<OscillatorParameters>& parameters, const std::string& name)
        : DetuneLookup (maxSize, parameters, name)
{

}
