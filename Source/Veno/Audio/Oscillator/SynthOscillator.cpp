#include "SynthOscillator.h"
#include "../../Utils.h"

SynthOscillator::SynthOscillator (const std::string& id, int maxVoices, const std::string& name)
        : BaseOscillator (id, name, maxVoices)
{
}

SynthOscillator::~SynthOscillator ()
{
}

double SynthOscillator::getValue ()
{
    return m_values[0];
}

void SynthOscillator::update ()
{

}

bool SynthOscillator::renderOsc ()
{
    int voices = m_parameters->m_voices->m_value;
    if (m_midiNote == 0 || voices == 0 || !m_parameters->m_active->m_value)
        return false;


    auto wheelPos = m_parameters->m_pitchWheel->m_value;
    double pitchPos = wheelPos >= 0 ? m_parameters->m_pitchUp->m_value : m_parameters->m_pitchDown->m_value;
    double pitchBend = wheelPos == 0 ? 0.0 : pitchPos * wheelPos;

    double midi = m_midiNote;
    if (m_isPorta)
        midi = m_midiNotePortamento.getNextValue ();

    auto semitones = m_parameters->m_semitones->getAsInt ();
    auto cents = m_parameters->m_cents->getValueForVoice (m_index) / 100;
    midi = VeNo::Utils::clamp (midi + semitones + cents + pitchBend, 0, 127);
    m_freq = std::exp ((midi - 69) * std::log (2) / 12) * 440.0f;

    m_widener->update ();
    m_DetuneHelper->update (m_freq, m_midiNote);
    m_filter->update ();

    if (!BaseOscillator::render ())
        return false;

    m_widener->apply (m_values, m_panning);
    m_filter->m_filter.processRaw (m_values);
    m_limiter->apply (m_values, m_panning);

    return true;
}
