#include "AudioConfig.h"
#include "../Audio/WaveTable/WaveTableGenerator.h"

std::shared_ptr<AudioConfig> AudioConfig::m_instance;
std::unordered_map<std::string, std::string> AudioConfig::m_instances;

double AudioConfig::getSampleRate () const
{
    return m_sampleRate;
}

void AudioConfig::setSampleRate (double _sampleRate)
{
    if (m_sampleRate != _sampleRate)
    {
        m_sampleRate = _sampleRate;
        m_needToReInit = true;
        this->initWaveTables ();
        m_needToReInit = false;
    }
}

double AudioConfig::getBufferSize () const
{
    return m_bufferSize;
}

void AudioConfig::setBufferSize (double _bufferSize)
{
    m_bufferSize = _bufferSize;
}

bool AudioConfig::isNeedToReInit () const
{
    return m_needToReInit;
}

void AudioConfig::setNeedToReInit (bool _needToReInit)
{
    m_needToReInit = _needToReInit;
}

std::shared_ptr<AudioConfig> AudioConfig::getInstance ()
{
    if (AudioConfig::m_instance == nullptr)
        AudioConfig::m_instance = std::make_shared<AudioConfig> ();
    return m_instance;
}

void AudioConfig::initWaveTables ()
{
    VeNo::WaveTableGenerator::getInstance ().cleanTables ();
    VeNo::WaveTableGenerator::getInstance ().init ();
}

AudioConfig::~AudioConfig ()
{
    VeNo::WaveTableGenerator::getInstance ().cleanTables ();
}

AudioConfig::AudioConfig ()
{

}

void AudioConfig::registerInstance (std::string& id)
{
    m_instances[id] = id;
}

void AudioConfig::deleteInstance (std::string& id)
{
    m_instances.erase (id);
    if (m_instances.empty ())
    {
        VeNo::WaveTableGenerator::getInstance ().cleanTables ();
        m_instance.reset ();
    }
}
