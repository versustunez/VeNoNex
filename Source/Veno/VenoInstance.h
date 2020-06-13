//
// Created by versustune on 09.06.20.
//

#ifndef VENO_VENOINSTANCE_H
#define VENO_VENOINSTANCE_H

#include "JuceHeader.h"
#include "Audio/Synth/SynthInstance.h"
#include "Utils/FFT.h"
#include "Audio/VenoBuffer.h"
#include <unordered_map>

class VenoInstance {
private:
    std::shared_ptr<SynthInstance> m_synthInstance;
    static std::unordered_map<std::string, std::shared_ptr<VenoInstance>> instances;
    std::string m_id;
public:
    static std::shared_ptr<VenoInstance> createInstance(const std::string& id);
    static std::shared_ptr<VenoInstance> getInstance(const std::string& id);
    explicit VenoInstance(std::string id);
    ~VenoInstance();
    const std::shared_ptr<SynthInstance> &getSynthInstance() const;
    static void deleteInstance(const std::string& processId);
    FFT fft;
    std::shared_ptr<VenoBuffer> audioBuffer;
};


#endif //VENO_VENOINSTANCE_H
