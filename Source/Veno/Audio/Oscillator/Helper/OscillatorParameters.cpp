#include "OscillatorParameters.h"

OscillatorParameters::OscillatorParameters (ParameterHandler* handler, const std::string& name)
:m_name(name + "__"), m_handler(handler)
{
    m_active = getParameter ("active");
    m_voices = getParameter ("voices");
    m_semitones = getParameter ("semitones");
    m_cents = getParameter ("cents");
    m_level = getParameter ("level");
    m_panning = getParameter ("panning");
    m_detuneAmount = getParameter ("detune_amount");
    m_detuneDense = getParameter ("detune_dense");
    m_detuneMode = getParameter ("detune_mode");
    m_phase = getParameter ("phase");
    m_randomPhase = getParameter ("random_phase");
    m_stereo = getParameter ("stereo");
    m_waveformPrimary = getParameter ("waveform_base");
    m_waveformSecond = getParameter ("waveform_sec");
    m_waveformMix = getParameter ("waveform_mix");

    m_pitchWheel = m_handler->getParameter ("pitch__wheel");
    m_pitchUp = m_handler->getParameter ("pitchbend__up");
    m_pitchDown = m_handler->getParameter ("pitchbend__down");
}

VeNoParameter* OscillatorParameters::getParameter (const std::string& name)
{
    return m_handler->getParameter (m_name + name);
}
