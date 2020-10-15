#include "WaveTableWrapper.h"
#include "../../../Core/AudioConfig.h"
#include "../../../Core/LookupTables.h"
#include "../../../Utils.h"

WaveTableWrapper::WaveTableWrapper (const std::string& name, std::shared_ptr<OscillatorParameters>& parameters,
                                    int maxVoices)
        : m_name (name), m_parameters (parameters)
{
    m_voices.resize (maxVoices);
    for (int i = 0; i < maxVoices; ++i)
    {
        m_voices[i] = new Voice ();
    }
}

bool WaveTableWrapper::prepare ()
{
    auto phase = m_parameters->m_phase->getValueForVoice (m_parameters->m_index);
    for (auto& voice : m_voices)
    {
        voice->m_phaseOfs = phase;
    }
    auto& waveTable = VeNo::WaveTableGenerator::getInstance ();
    auto baseWaveTable = m_parameters->m_waveformPrimary->getValue () - 1;
    auto secondWaveTable = m_parameters->m_waveformSecond->getValue () - 1;
    m_baseWaveGroup = waveTable.getGroup (baseWaveTable);
    m_currentWaveGroup = waveTable.getGroup (secondWaveTable);
    return m_currentWaveGroup != nullptr && m_baseWaveGroup != nullptr;
}

void WaveTableWrapper::setFrequency (int untilIndex, double baseFreq, std::shared_ptr<DetuneHelper>& detuneHelper)
{
    if (m_currentWaveGroup == nullptr && !prepare ())
    {
        return;
    }
    // performance ;)
    double sRate = AudioConfig::getInstance ()->m_sampleRate;
    auto detune = detuneHelper->getDetune();
    for (int index = 0; index < untilIndex; ++index)
    {
        double inc = detune->m_frequency * detune->m_lookup[index] / sRate;
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
}

void WaveTableWrapper::setRandomPhase ()
{
    std::srand (135035011);
    for (auto& m_voice : m_voices)
    {
        m_voice->m_phasor = (double) std::rand () / RAND_MAX;
    }
}

void WaveTableWrapper::reset ()
{
    for (auto& voice : m_voices)
    {
        voice->m_phasor = 0;
    }
}

double WaveTableWrapper::getOutput (int index)
{
    auto cVoice = m_voices[index];
    cVoice->m_phasor += cVoice->m_phaseInc;
    if (cVoice->m_phasor >= 1.0)
        cVoice->m_phasor -= 1.0;
    if (cVoice->m_phaseOfs > 0)
    {
        return getOutputPWM (index) * LookupTables::detuneLookup[index];
    }
    return getOutputRaw (index, 0) * LookupTables::detuneLookup[index];
}

double WaveTableWrapper::getOutputRaw (int index, double offset)
{
    auto cVoice = m_voices[index];
    if (cVoice->m_baseWaveTable != nullptr)
    {
        auto mixValue = m_parameters->m_waveformMix->getValue ();
        double phase = (double) cVoice->m_phasor + offset;
        auto sum = getWaveTableValue (cVoice->m_baseWaveTable, phase);
        auto finalSum = getWaveTableValue (cVoice->m_currentWaveTable, phase);
        return VeNo::Utils::waveTableMix (sum, finalSum, mixValue);
    }
    return 0;
}

double WaveTableWrapper::getOutputPWM (int index)
{
    auto offset = m_voices[index]->m_phaseOfs;
    double sumOne = getOutputRaw (index, 0);
    double sumTwo = getOutputRaw (index, offset);
    return VeNo::Utils::clamp ((sumOne + sumTwo) / 2, -1, 1);
}

double WaveTableWrapper::getWaveTableValue (VeNo::WaveTableObject* table, double phase)
{
    if (table == nullptr)
    {
        return 0.0;
    }
    if (phase > 1.0)
    {
        phase -= 1.0;
    }
    double val = phase * (double) table->m_waveTableLen;
    int value = (int) val;
    int temp = (int) val + 1;
    double sum = table->m_waveTable[value];
    double sum2 = table->m_waveTable[temp];

    double fraction = val - (double) value;
    double finalSum = sum + fraction * (sum2 - sum);
    return finalSum;
}

WaveTableWrapper::~WaveTableWrapper ()
{
    for (auto& voice : m_voices)
    {
        delete voice;
    }
}
