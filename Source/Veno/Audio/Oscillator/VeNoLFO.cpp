#include "VeNoLFO.h"
#include "../../VenoInstance.h"

VeNoLFO::VeNoLFO (const std::string& id, int maxVoices, const std::string& name)
        : BaseOscillator (id, name, maxVoices),
        m_freqRate(VenoInstance::getInstance(m_id)->handler->getParameter(name + "__rate"))
{
    m_midiNote = 69; // 440Hz A4!
    for (auto& m_voice : m_voices)
    {
        m_voice->m_isMono = true;
    }
}

double VeNoLFO::getValue ()
{
    return BaseOscillator::getMonoValue ();
}

VeNoLFO::~VeNoLFO ()
{
    BaseOscillator::~BaseOscillator ();
}

void VeNoLFO::update ()
{
    render ();
}

bool VeNoLFO::postProcessing ()
{
    m_limiter->apply (m_values, m_panning);
    return true;
}

bool VeNoLFO::preProcessing ()
{
    m_DetuneHelper->update (m_freq, m_midiNote);
    return true;
}

void VeNoLFO::setFrequency ()
{
    m_freq = m_freqRate->getValue ();
}

bool VeNoLFO::render ()
{
    int voices = m_parameters->m_voices->getAsInt ();
    if (m_midiNote == 0 || voices == 0 || !m_parameters->m_active->getAsBoolean ())
        return false;
    setFrequency ();
    if (!preProcessing () || !BaseOscillator::render () || !postProcessing ())
        return false;
    return true;
}
