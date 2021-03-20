#include "VeNoXDetune.h"
#include "../../../../Utils.h"

void VeNoXDetune::prepareDetune (int voices)
{
    double detune = m_parameters->m_detuneDense->getValueForVoice(m_parameters->m_index);
    if (!isInit || voices != m_lastVoices || m_lastDetune != detune)
    {
        if (voices == 1)
            return;
        isInit = true;
        m_lastDetune = detune;
        getRealDetune ();
        m_lastDetune = detune;
        m_lookup[0] = 1;

        double split = m_currentDetune / voices;
        double cents = m_currentDetune;
        for (int i = 1; i < voices; ++i)
        {
            double plus;
            if ((i & 1) == 1)
            {
                plus = VeNo::Utils::centsToRatio (-cents);
            }
            else
            {
                plus = VeNo::Utils::centsToRatio (cents);
            }
            cents -= split;
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
