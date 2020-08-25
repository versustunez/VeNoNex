#include "WaveTableWrapper.h"
#include "../../../Core/AudioConfig.h"
#include "../../../Core/LookupTables.h"
#include "../../../Utils.h"
#include "../../../Utils/VeNoParameterStringHelper.h"

WaveTableWrapper::WaveTableWrapper (const std::string& name, std::shared_ptr<OscillatorParameters>& parameters,
                                    int maxVoices)
{
    m_name = name;
    m_parameters = parameters;
    m_voices.resize (maxVoices);
    for (int i = 0; i < maxVoices; ++i)
    {
        m_voices[i] = new Voice ();
    }
}

bool WaveTableWrapper::prepare ()
{
    auto phase = m_parameters->m_phase->getValue ();
    for (auto& voice : m_voices)
    {
        voice->m_phaseOfs = phase;
    }
    auto baseWaveTable = m_parameters->m_waveformPrimary->getValue () - 1;
    auto secondWaveTable = m_parameters->m_waveformSecond->getValue () - 1;
    m_baseWaveGroup = WaveTableGenerator::getInstance ().getGroup (baseWaveTable);
    m_currentWaveGroup = WaveTableGenerator::getInstance ().getGroup (secondWaveTable);
    return m_currentWaveGroup != nullptr && m_baseWaveGroup != nullptr;
}

void WaveTableWrapper::setFrequencyForVoice (int index, float freq)
{
    if (m_currentWaveGroup == nullptr && !prepare ())
    {
        return;
    }
    float inc = freq / AudioConfig::getInstance ()->getSampleRate ();
    auto currentVoice = m_voices[index];
    //something is complete wrong!
    currentVoice->m_phaseInc = inc;
    if (index == 0)
    {
        int curWaveTable = 0;
        while ((curWaveTable < (m_currentWaveGroup->m_numWaveTables - 1) &&
                (inc >= m_currentWaveGroup->m_WaveTables[curWaveTable]->m_topFreq)))
        {
            ++curWaveTable;
        }
        currentVoice->m_currentWaveTable = m_currentWaveGroup->m_WaveTables[curWaveTable];

        if (m_currentWaveGroup != m_baseWaveGroup)
        {
            curWaveTable = 0;
            while ((curWaveTable < (m_baseWaveGroup->m_numWaveTables - 1) &&
                    (inc >= m_baseWaveGroup->m_WaveTables[curWaveTable]->m_topFreq)))
            {
                ++curWaveTable;
            }
        }
        currentVoice->m_baseWaveTable = m_baseWaveGroup->m_WaveTables[curWaveTable];
    }
    else
    {
        currentVoice->m_currentWaveTable = m_voices[0]->m_currentWaveTable;
        currentVoice->m_baseWaveTable = m_voices[0]->m_baseWaveTable;
    }
}

void WaveTableWrapper::setRandomPhase ()
{
    std::srand (1);
    for (auto& m_voice : m_voices)
    {
        m_voice->m_phasor = std::rand () / RAND_MAX;
    }
}

void WaveTableWrapper::reset ()
{
    for (auto& voice : m_voices)
    {
        voice->m_phasor = 0;
    }
}

void WaveTableWrapper::updatePhase (int index)
{
    auto cVoice = m_voices[index];
    cVoice->m_phasor += cVoice->m_phaseInc;
    if (cVoice->m_phasor >= 1.0)
        cVoice->m_phasor -= 1.0;
}

float WaveTableWrapper::getOutput (int index)
{
    auto cVoice = m_voices[index];
    if (cVoice->m_phaseOfs > 0)
    {
        return getOutputPWM (index) * LookupTables::detuneLookup[index];
    }
    return getOutputRaw (index, 0) * LookupTables::detuneLookup[index];
}

float WaveTableWrapper::getOutputRaw (int index, float offset)
{
    auto cVoice = m_voices[index];
    if (cVoice->m_baseWaveTable != nullptr)
    {
        auto mixValue = m_parameters->m_waveformMix->getValue ();
        float phase = (float) cVoice->m_phasor + offset;
        auto sum = getWaveTableValue (cVoice->m_baseWaveTable, phase);
        auto finalSum = getWaveTableValue (cVoice->m_currentWaveTable, phase);
        return VeNo::Utils::waveTableMix (sum, finalSum, mixValue);
    }
    return 0;
}

float WaveTableWrapper::getOutputPWM (int index)
{
    auto offset = m_voices[index]->m_phaseOfs;
    float sumOne = getOutputRaw (index, 0);
    float sumTwo = getOutputRaw (index, offset);
    return VeNo::Utils::clamp ((sumOne + sumTwo) / 2, -1, 1);
}

float WaveTableWrapper::getWaveTableValue (WaveTableObject* table, float phase)
{
    if (table == nullptr)
    {
        return 0.0;
    }
    if (phase > 1.0)
    {
        phase -= 1.0;
    }
    float val = phase * (float) table->m_waveTableLen;
    int value = (int) val;
    int temp = (int) val + 1;
    if (temp > table->m_waveTableLen)
    {
        temp -= table->m_waveTableLen;
    }
    float sum = table->m_waveTable[value];
    float sum2 = table->m_waveTable[temp];

    float fraction = val - (float) value;
    float finalSum = sum + fraction * (sum2 - sum);
    return finalSum;
}

WaveTableWrapper::~WaveTableWrapper ()
{
    for (auto& voice : m_voices)
    {
        delete voice;
    }
}
