//
// Created by versustune on 09.06.20.
//

#ifndef VENO_VENOINSTANCE_H
#define VENO_VENOINSTANCE_H

#include "JuceHeader.h"
#include "Audio/Synth/SynthInstance.h"
#include "Utils/FFT.h"
#include "Audio/VenoBuffer.h"
#include "Audio/Engine/VenoMatrix.h"
#include "Core/VeNoState.h"
#include <unordered_map>

class VenoInstance
{
private:
    std::shared_ptr<SynthInstance> m_synthInstance;
    static std::unordered_map<std::string, std::shared_ptr<VenoInstance>> instances;
    std::string m_id;
public:
    explicit VenoInstance (std::string id);
    ~VenoInstance ();
    static std::shared_ptr<VenoInstance> createInstance (const std::string& id);
    static std::shared_ptr<VenoInstance> getInstance (const std::string& id);
    static void deleteInstance (const std::string& processId);
    const std::shared_ptr<SynthInstance>& getSynthInstance () const;
    FFT fft;
    std::shared_ptr<VenoBuffer> audioBuffer;
    VenoMatrix matrix{m_id}; //matrix need a own xml profile to save and restore!
    VeNoState* state;
    static std::unordered_map<std::string, std::shared_ptr<VenoInstance>> getAll ();
};
#endif //VENO_VENOINSTANCE_H
