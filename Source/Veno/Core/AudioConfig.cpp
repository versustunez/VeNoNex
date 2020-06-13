//
// Created by versustune on 22.03.20.
//
#include "AudioConfig.h"
#include "../Audio/WaveTable/WaveTableGenerator.h"

std::shared_ptr<AudioConfig> AudioConfig::m_instance;

float AudioConfig::getSampleRate ()
{
    return m_sampleRate;
}

void AudioConfig::setSampleRate (float _sampleRate)
{
    if (m_sampleRate != _sampleRate)
    {
        m_sampleRate = _sampleRate;
        m_needToReInit = true;
    }
}

float AudioConfig::getBufferSize ()
{
    return m_bufferSize;
}

void AudioConfig::setBufferSize (float _bufferSize)
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
    WaveTableGenerator::getInstance ().init ();
}

AudioConfig::~AudioConfig ()
{
    WaveTableGenerator::getInstance ().cleanTables ();
}
