/**
 * TODO: Make Save of the Parameter Getter... the lookup takes alot of time! also Pre-Calc values if not change
 */
#include "BaseOscillator.h"
#include "../../Utils.h"
#include "../../VenoInstance.h"
#include "../../Utils/VeNoParameterStringHelper.h"

BaseOscillator::BaseOscillator(const std::string& id, const std::string& name, int maxVoices)
{
    m_id = id;
    m_name = name;
    m_maxVoices = maxVoices;
    m_handler = VenoInstance::getInstance(m_id)->handler;
    m_parameters = std::make_shared<OscillatorParameters>(m_handler, m_name);
    m_values.resize(3);
    m_panning.resize(2);
    if (maxVoices == 1)
    {
        m_hasDetune = false;
    }
    initModules();
    m_voices.resize(maxVoices);
    for (int i = 0; i < maxVoices; ++i)
    {
        m_voices[i] = new OscillatorVoice(id, m_waveTableHelper, m_DetuneHelper, m_widener, i);
    }
}

void BaseOscillator::initModules()
{
    m_waveTableHelper = std::make_shared<WaveTableWrapper>(m_name, m_parameters, m_maxVoices);
    m_DetuneHelper = std::make_shared<DetuneHelper>(m_name, m_parameters, m_maxVoices);
    m_widener = std::make_shared<Widener>(m_name, m_parameters);
    m_limiter = std::make_shared<Limiter>(m_name, m_parameters);
}

bool BaseOscillator::start(int currentMidiNote)
{
    if (currentMidiNote == 0 ||
        !m_handler->getParameter(VeNoParameterStringHelper::getForOscillator(m_name, 0))->getAsBoolean())
    {
        return false;
    }
    m_midiNote = currentMidiNote;
    if (!m_waveTableHelper->prepare())
    {
        DBG("SELECT IS FALSE!");
    }
    if (m_handler->getParameter(VeNoParameterStringHelper::getForOscillator(m_name, 10))->getAsBoolean())
    {
        m_waveTableHelper->setRandomPhase();
    }
    return true;
}

void BaseOscillator::stop()
{
    m_panning[0] = 0;
    m_panning[1] = 0;
    m_midiNote = 0;
}

bool BaseOscillator::render()
{
    int voices = m_parameters->m_voices->getAsInt();
    if (m_midiNote == 0 || voices == 0 || !m_parameters->m_active->getAsBoolean())
    {
        return false;
    }
    setFrequency();
    m_widener->update();
    m_DetuneHelper->update(m_freq, m_midiNote);
    float detuneOutput = 0.0;
    m_voices[0]->processValue(m_freq);
    m_values[0] = m_voices[0]->getMonoValue() * 0.75;
    m_values[1] = 0;
    m_values[2] = 0;
    m_panning[0] = 0;
    m_panning[1] = 0;
    for (int i = 1; i < voices; ++i)
    {
        m_voices[i]->processValue(m_freq);
        m_panning[0] += m_voices[i]->getLeftValue();
        m_panning[1] += m_voices[i]->getRightValue();
        detuneOutput += m_voices[i]->getMonoValue();
    }
    detuneOutput /= (float) voices;
    detuneOutput *= m_parameters->m_detuneAmount->getValue();
    m_values[0] += detuneOutput;
    float volumeLevel = m_parameters->m_level->getValue();
    m_values[0] *= volumeLevel;
    m_panning[0] *= volumeLevel;
    m_panning[1] *= volumeLevel;
    applyModules();
    return true;
}

bool BaseOscillator::applyModules()
{
    m_widener->apply(m_values, m_panning);
    m_limiter->apply(m_values, m_panning);
    return true;
}

void BaseOscillator::setFrequency()
{
    float midi = m_midiNote;
    auto semitones = m_parameters->m_semitones->getAsInt();
    auto cents = m_parameters->m_cents->getAsInt() / 100;
    midi = VeNo::Utils::clamp(midi + semitones + cents + getPitchBend(), 1, 127);
    m_freq = std::exp((midi - 69) * std::log(2) / 12) * 440.0f;
}

float BaseOscillator::getPitchBend()
{
    auto wheelPos = m_parameters->m_pitchWheel->getValue();
    if (wheelPos == 0)
    {
        return 0;
    }
    if (wheelPos > 0)
    {
        return m_parameters->m_pitchUp->getValue() * wheelPos;
    }
    else
    {
        return m_parameters->m_pitchDown->getValue() * wheelPos;
    }
}

BaseOscillator::~BaseOscillator()
{
    m_limiter.reset();
    m_DetuneHelper.reset();
    m_widener.reset();
    m_waveTableHelper.reset();
    m_handler = nullptr;
    m_parameters.reset();
    for (auto& m_voice : m_voices)
    {
        delete m_voice;
    }
    m_voices.clear();
}

const std::vector<float>& BaseOscillator::getValue()
{
    return m_values;
}

float BaseOscillator::getLeftValue()
{
    return m_values[1];
}

float BaseOscillator::getRightValue()
{
    return m_values[2];
}

float BaseOscillator::getMonoValue()
{
    return m_values[0];
}
