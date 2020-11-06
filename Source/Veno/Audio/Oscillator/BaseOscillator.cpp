/**
 * TODO: Make Save of the Parameter Getter... the lookup takes alot of time! also Pre-Calc values if not change
 */
#include "BaseOscillator.h"
#include "../../Utils.h"
#include "../../VenoInstance.h"
#include "../../Core/AudioConfig.h"

BaseOscillator::BaseOscillator (const std::string& id, const std::string& name, int maxVoices)
        : m_id (id), m_name(name), m_handler(VenoInstance::getInstance(m_id)->handler), m_maxVoices(maxVoices)
{
    m_handler = VenoInstance::getInstance (m_id)->handler;
    m_parameters = std::make_shared<OscillatorParameters> (m_handler, m_name);
    m_values.resize (3);
    m_panning.resize (2);
    if (maxVoices == 1)
    {
        m_hasDetune = false;
    }
    initModules ();
}

void BaseOscillator::initModules ()
{
    m_waveTableHelper = std::make_shared<WaveTableWrapper> (m_name, m_parameters, m_maxVoices);
    m_DetuneHelper = std::make_shared<DetuneHelper> (m_name, m_parameters, m_maxVoices);
    m_widener = std::make_shared<Widener> (m_name, m_parameters);
    m_limiter = std::make_shared<VeNo::Limiter> (m_name, m_parameters);
    m_filter = std::make_unique<VeNo::OscillatorFilter>(m_id, m_name);
}

bool BaseOscillator::start (int currentMidiNote, bool legato)
{
    if (currentMidiNote <= 0 || !m_parameters->m_active->getAsBoolean ())
        return false;


    m_isPorta = legato;
    if (legato)
    {
        if (m_lastPortamento != m_parameters->m_portamento->m_value)
        {
            m_midiNotePortamento.reset (AudioConfig::getInstance ()->getSampleRate (),
                                        m_parameters->m_portamento->m_value);
            m_lastPortamento = m_parameters->m_portamento->m_value;
        }
        if (m_midiNote <= 0)
        {
            m_midiNotePortamento.setCurrentAndTargetValue (currentMidiNote);
        }
        else
        {
            m_midiNotePortamento.setTargetValue (currentMidiNote);
        }
    } else {
        m_midiNotePortamento.setCurrentAndTargetValue (currentMidiNote);
    }
    m_midiNote = currentMidiNote;
    if (!m_waveTableHelper->prepare ())
        return false;

    if (m_parameters->m_randomPhase->getAsBoolean () && !legato)
        m_waveTableHelper->setRandomPhase ();
    return true;
}

void BaseOscillator::stop ()
{
    m_panning[0] = 0;
    m_panning[1] = 0;
    m_midiNote = 0;
}

bool BaseOscillator::render ()
{
    int voices = m_parameters->m_voices->getAsInt ();
    m_waveTableHelper->setFrequency(voices, m_freq, m_DetuneHelper);
    m_values[0] = m_waveTableHelper->getOutput(0);
    m_panning[0] = 0;
    m_panning[1] = 0;
    if (voices > 1)
    {
        double detuneOutput = 0.0;
        for (int i = 1; i < voices; ++i)
        {
            auto val = m_waveTableHelper->getOutput(i);
            m_panning[i & 1] += val * 0.33333333;
            detuneOutput += val;
        }
        double dAmount = m_parameters->m_detuneAmount->m_voiceValues[m_index];
        detuneOutput *= dAmount;
        detuneOutput /= (double) (voices - 1);
        m_values[0] += detuneOutput;
        m_panning[0] *= dAmount;
        m_panning[1] *= dAmount;
    }
    double volumeLevel = m_parameters->m_level->m_voiceValues[m_index];
    m_values[0] *= volumeLevel;
    m_panning[0] *= volumeLevel;
    m_panning[1] *= volumeLevel;
    return true;
}

BaseOscillator::~BaseOscillator ()
{
    m_limiter.reset ();
    m_DetuneHelper.reset ();
    m_widener.reset ();
    m_waveTableHelper.reset ();
    m_handler = nullptr;
    m_parameters.reset ();
}

const std::vector<double>& BaseOscillator::getValue ()
{
    return m_values;
}

double BaseOscillator::getLeftValue ()
{
    return m_values[1];
}

double BaseOscillator::getRightValue ()
{
    return m_values[2];
}

double BaseOscillator::getMonoValue ()
{
    return m_values[0];
}

void BaseOscillator::setIndex (int index)
{
    m_index = index;
    m_parameters->m_index = index;
    m_filter->m_voice = index;
}
