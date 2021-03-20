#include "SuperDetune.h"
#include "../../../../Utils.h"

void SuperDetune::prepareDetune (int voices)
{
    double detune = m_parameters->m_detuneDense->getValueForVoice(m_parameters->m_index);
    if (!isInit || voices != m_lastVoices || m_lastDetune != detune)
    {
        if (voices == 1)
            return;
        isInit = true;
        m_lastDetune = detune;
        getRealDetune ();
        m_lookup[0] = 1;

        double split = m_currentDetune / (voices - 1);
        double cents = split;
        for (int i = 1; i < voices; ++i)
        {
            double plus;
            if ((i & 1) == 1)
            {
                plus = VeNo::Utils::centsToRatio (-cents * m_superLookup[m_midiNote-1]);
            }
            else
            {
                plus = VeNo::Utils::centsToRatio (cents * m_superLookup[m_midiNote-1]);
            }
            cents += split;
            m_lookup[i] = plus;
        }
    }
    m_lastVoices = voices;
}

void SuperDetune::getRealDetune ()
{
    double d = m_lastDetune / m_detuneCents;
    if (d > 0.5f)
    {
        d = 0.5f + (d * d * 0.5f);
    }
    m_currentDetune = d * m_detuneCents;

}

void SuperDetune::prepareSuperLookup ()
{
    double biggest = 0.14173228346456693;
    if (m_superLookup.size () != 128 || m_superLookup.empty ())
    {
        m_superLookup.resize (128);
        for (int i = 0; i < 127; ++i)
        {
            m_superLookup[i] = 1 + (int(i / 7.0) / 127.0) - biggest;
        }
    }
}

SuperDetune::SuperDetune (int maxSize, std::shared_ptr<OscillatorParameters>& parameters, const std::string& name)
        : DetuneLookup (maxSize, parameters, name)
{
    prepareSuperLookup ();
}
