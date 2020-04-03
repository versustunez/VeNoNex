//
// Created by versustune on 22.03.20.
//

#ifndef VENO_AUDIOCONFIG_H
#define VENO_AUDIOCONFIG_H

#include "JuceHeader.h"

/**
 * holds SampleRate and other needed sound information's :)
 */
class AudioConfig {
private:
    static std::shared_ptr<AudioConfig> instance;
    float sampleRate = 44100;
    float bufferSize = 512; //maybe we need that... but this will update always!
    bool needToReInit = false; //this is to reInit the Oscillators, ADSR and other stuff
public:
    static std::shared_ptr<AudioConfig> getInstance() {
        if (!instance)
            instance = std::make_shared<AudioConfig>();
        return instance;
    }

    float getSampleRate() const {
        return sampleRate;
    }

    void setSampleRate(float _sampleRate) {
        if (sampleRate != _sampleRate) {
            sampleRate = _sampleRate;
            needToReInit = true;
        }
    }

    float getBufferSize() const {
        return bufferSize;
    }

    void setBufferSize(float _bufferSize) {
        AudioConfig::bufferSize = _bufferSize;
    }

    bool isNeedToReInit() const {
        return needToReInit;
    }

    void setNeedToReInit(bool _needToReInit) {
        AudioConfig::needToReInit = _needToReInit;
    }

protected:
};


#endif //VENO_AUDIOCONFIG_H
