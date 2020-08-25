#include "OscillatorParameters.h"
#include "../../../Utils/VeNoParameterStringHelper.h"

OscillatorParameters::OscillatorParameters(ParameterHandler* handler, const std::string& name)
{
    m_name = name;
    m_handler = handler;
    m_active= getParameter(0);
    m_voices = getParameter(1);
    m_semitones = getParameter(2);
    m_cents = getParameter(3);
    m_level = getParameter(4);
    m_panning = getParameter(5);
    m_detuneAmount = getParameter(6);
    m_detuneDense = getParameter(7);
    m_detuneMode = getParameter(8);
    m_phase = getParameter(9);
    m_randomPhase = getParameter(10);
    m_stereo = getParameter(11);
    m_waveformPrimary = getParameter(16);
    m_waveformSecond = getParameter(17);
    m_waveformMix = getParameter(18);

    m_pitchWheel = m_handler->getParameter("pitch__wheel");
    m_pitchUp = m_handler->getParameter("pitchbend__up");
    m_pitchDown = m_handler->getParameter("pitchbend__down");
}

VeNoParameter* OscillatorParameters::getParameter(int index)
{
    return m_handler->getParameter(VeNoParameterStringHelper::getForOscillator(m_name, index));
}
