#include "VeNoLFO.h"
#include "../../VenoInstance.h"

VeNoLFO::VeNoLFO (const std::string& id, int maxVoices, const std::string& name)
        : BaseOscillator (id, name, maxVoices),
        m_freqRate(VenoInstance::getInstance(m_id)->handler->getModulateValue(name + "__rate").get())
{
    m_midiNote = 69; // 440Hz A4!
}

double VeNoLFO::getValue ()
{
    return m_value;
}

VeNoLFO::~VeNoLFO ()
{
}

void VeNoLFO::update ()
{
    int voices = m_parameters->m_voices->m_value;
    if (!m_parameters->m_active->getAsBoolean ())
        return;
    m_freq = m_freqRate->m_voiceValues[m_index];
    m_waveTableHelper->prepare();
    m_DetuneHelper->update(m_freq, m_midiNote);

    BaseOscillator::render ();
    m_limiter->apply(m_values, m_panning);
    m_value = BaseOscillator::m_values[0];
}
