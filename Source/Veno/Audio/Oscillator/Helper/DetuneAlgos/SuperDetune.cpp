#include "SuperDetune.h"
#include "../../../../Utils.h"
#include "../../../../Utils/VeNoParameterStringHelper.h"

void SuperDetune::prepareDetune (int voices)
{
    prepareSuperLookup ();
    float detune = m_parameters->m_detuneDense->getValueForVoice(m_parameters->m_index);
    if (m_lookup.empty () || voices != m_lastVoices || m_lastDetune != detune)
    {
        m_lastDetune = detune;
        getRealDetune ();
        m_lookup[0] = 1;

        if (voices == 1)
        {
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
                plus = VeNo::Utils::centsToRatio (-cents) * m_superLookup[m_midiNote];
            }
            else
            {
                plus = VeNo::Utils::centsToRatio (cents) * m_superLookup[m_midiNote];
            }
            m_lookup[i] = plus;
        }
    }
    m_lastVoices = voices;
}

void SuperDetune::getRealDetune ()
{
    float d = m_lastDetune / m_detuneCents;
    if (d > 0.5f)
    {
        d = 0.5f + (d * d * 0.5f);
    }
    m_currentDetune = d * m_detuneCents;

}

void SuperDetune::prepareSuperLookup ()
{
    if (m_superLookup.size () != 128 || m_superLookup.empty ())
    {
        m_superLookup.resize (128);
        for (int i = 0; i < 127; ++i)
        {
            m_superLookup[i] = int (i / 7) / 127;
        }
    }
}

SuperDetune::SuperDetune (int maxSize, std::shared_ptr<OscillatorParameters>& parameters, const std::string& name)
        : DetuneLookup (maxSize, parameters, name)
{

}
