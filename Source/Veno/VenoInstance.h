#ifndef VENO_VENOINSTANCE_H
#define VENO_VENOINSTANCE_H

#include "JuceHeader.h"
#include "Audio/Synth/SynthInstance.h"
#include "Services/FFT.h"
#include "Audio/VenoBuffer.h"
#include "Audio/Engine/VeNoMatrix.h"
#include "Core/VeNoState.h"
#include "Core/ParameterHandler.h"
#include "Core/VeNoChangeListener.h"
#include "Core/PresetManager.h"
#include "Audio/Engine/AudioModulators.h"
#include <unordered_map>

class VenoInstance
{
private:
    std::string m_id;
    std::shared_ptr<VeNo::Synth::Synthesizer> m_synthInstance;
    static std::unordered_map<std::string, std::shared_ptr<VenoInstance>> instances;
public:
    explicit VenoInstance (const std::string& id);

    ~VenoInstance ();

    static std::shared_ptr<VenoInstance> createInstance (const std::string& id);

    static std::shared_ptr<VenoInstance> getInstance (const std::string& id);

    static void deleteInstance (const std::string& processId);

    static bool hasInstance (const std::string& id);

    [[nodiscard]] const std::shared_ptr<VeNo::Synth::Synthesizer>& getSynthInstance () const;

    std::shared_ptr<VenoBuffer> audioBuffer;
    VeNoMatrix* matrix; //matrix need a own xml profile to save and restore!
    VeNoState* state;
    ParameterHandler* handler;
    VeNoChangeListener* changeListener;
    PresetManager* presetManager;
    AudioProcessorValueTreeState* treeState = nullptr;
    VeNo::AudioModulators* modulators;
    OpenGLContext* glContext;

    static std::unordered_map<std::string, std::shared_ptr<VenoInstance>> getAll ();

protected:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (VenoInstance);
};

#endif //VENO_VENOINSTANCE_H
