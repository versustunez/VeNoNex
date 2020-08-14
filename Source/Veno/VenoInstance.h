//
// Created by versustune on 09.06.20.
//

#ifndef VENO_VENOINSTANCE_H
#define VENO_VENOINSTANCE_H

#include "JuceHeader.h"
#include "Audio/Synth/SynthInstance.h"
#include "Utils/FFT.h"
#include "Audio/VenoBuffer.h"
#include "Audio/Engine/VeNoMatrix.h"
#include "Core/VeNoState.h"
#include "Core/ParameterHandler.h"
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
    static bool hasInstance(const std::string& id);
    const std::shared_ptr<SynthInstance>& getSynthInstance () const;
    std::shared_ptr<VenoBuffer> audioBuffer;
    VeNoMatrix* matrix; //matrix need a own xml profile to save and restore!
    VeNoState* state;
    ParameterHandler* handler;
    static std::unordered_map<std::string, std::shared_ptr<VenoInstance>> getAll ();
protected:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (VenoInstance);
};
#endif //VENO_VENOINSTANCE_H
