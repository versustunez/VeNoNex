#include "OscillatorVoice.h"

OscillatorVoice::OscillatorVoice (const std::string& id, std::shared_ptr<WaveTableWrapper>& waveTableWrapper,
                                  std::shared_ptr<DetuneHelper>& detuneHelper,
                                  std::shared_ptr<Widener>& widener, int index)
        : m_id (id), m_waveTableWrapper (waveTableWrapper), m_detuneHelper (detuneHelper), m_widener (widener),
          m_index (index), m_isCenter(m_index == 0), m_isLeft((m_index & 1) == 1)
{
    m_values.resize (3);
}

OscillatorVoice::~OscillatorVoice ()
{
    m_waveTableWrapper.reset ();
    m_widener.reset ();
    m_detuneHelper.reset ();
}

void OscillatorVoice::processValue (double freq)
{
    m_waveTableWrapper->setFrequencyForVoice (m_index, m_detuneHelper->getDetuneFreq (m_index));
    auto value = m_waveTableWrapper->getOutput (m_index);
    m_waveTableWrapper->updatePhase (m_index);
    m_values[0] = value;
    if (m_isCenter || m_isMono)
        return;
    if (m_isLeft)
        m_values[1] = value * m_widener->getDetunePan ();
    else
        m_values[2] = value * m_widener->getDetunePan ();
}

double OscillatorVoice::getLeftValue ()
{
    return m_values[1];
}

double OscillatorVoice::getRightValue ()
{
    return m_values[2];
}

double OscillatorVoice::getMonoValue ()
{
    return m_values[0];
}
