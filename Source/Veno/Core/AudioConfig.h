#ifndef VENO_AUDIOCONFIG_H
#define VENO_AUDIOCONFIG_H

#include <unordered_map>
#include "JuceHeader.h"

/**
 * holds SampleRate and other needed sound information's :)
 */
class AudioConfig
{
private:
    static std::shared_ptr<AudioConfig> m_instance;
    float m_sampleRate = 0;
    float m_bufferSize = 512; //maybe we need that... but this will update always!
    bool m_needToReInit = false; //this is to reInit the Oscillators, ADSR and other stuff
    static std::unordered_map<std::string, std::string> m_instances;
public:
    static std::shared_ptr<AudioConfig> getInstance ();

    float getSampleRate () const;

    void setSampleRate (float _sampleRate);

    float getBufferSize () const;

    void setBufferSize (float _bufferSize);

    bool isNeedToReInit () const;

    void setNeedToReInit (bool _needToReInit);

    void initWaveTables ();

    AudioConfig ();

    ~AudioConfig ();

    static void registerInstance (std::string& id);

    static void deleteInstance (std::string& id);

protected:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AudioConfig);
};

#endif //VENO_AUDIOCONFIG_H
