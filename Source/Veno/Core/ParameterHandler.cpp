#include "ParameterHandler.h"

#include "../VenoInstance.h"

ParameterHandler::ParameterHandler(const std::string& id)
{
    m_id = id;
}

ParameterHandler::~ParameterHandler()
{
    DBG("Deleting Parameter Handler");
    params.clear();
}

void
ParameterHandler::addParameter(const std::string& name, const std::string& showName, float min, float max, float value,
                               ParameterTypes type)
{
    switch (type)
    {
        case Integer:
            params.push_back(std::make_unique<AudioParameterInt>(name, showName, min, max, value));
            break;
        case Float:
            params.push_back(std::make_unique<AudioParameterFloat>(name, showName, min, max, value));
            break;
        case Boolean:
            params.push_back(std::make_unique<AudioParameterBool>(name, showName, value == 1));
            break;
    }
}

AudioProcessorValueTreeState::ParameterLayout ParameterHandler::setupProcessor()
{
    if (params.empty())
    {
        setupParameter();
    }
    return {params.begin(), params.end()};
}

void ParameterHandler::addParameterModulate(const std::string& name, const std::string& showName, float min, float max,
                                            float value, ParameterTypes type)
{
    // no support for Boolean Modulations!
    if (type == ParameterTypes::Boolean)
    {
        return;
    }
    auto modulateValue = new ModulateValue(name, m_id);
    modulateValue->set(value, max, min);
    VenoInstance::getInstance(m_id)->matrix->addModulateValue(name, modulateValue);
    addParameter(name, showName, min, max, value, type);
}

/**
    master__volume | Modulate
    pitch__wheel | Not Modulate
    pitchbend__up | Not Modulate
    pitchbend__down | Not Modulate

    per OSC:
    active | not Modulate << to deactivate them from modulation turn the volume down to 0 ;) it will skip the renderer
    voices | not Modulate
    semitones | not Modulate | * 100 to get cents and add to fine cents

    cents | Modulate
    level | Modulate
    panning | Modulate
    detune_amount | Modulate
    detune_dense | Modulate
    detune_mode | not Modulate
    phase | Modulate
    random_phase | not Modulate
    stereo | Modulate
    attack | not Modulate
    decay | not Modulate
    sustain | not Modulate
    release | not Modulate
    waveform | not Modulate
    waveform_mix | Modulate
 */
void ParameterHandler::setupParameter()
{
    addParameterModulate("master__volume", "Synth Volume", 0.0f, 1.5f, 1.0f, Float);
    addParameter("pitch__wheel", "Pitch Wheel", -1.0f, 1.0f, 0, Float);
    addParameter("pitchbend__up", "Pitch Bend Up", 0, 36, 12, Integer);
    addParameter("pitchbend__down", "Pitch Bend Down", 0, 36, 12, Integer);
    for (int i = 1; i < 5; ++i)
    {
        std::string id = "osc" + std::to_string(i) + "__";
        std::string name = "OSC" + std::to_string(i) + " ";
        addParameter(id + "active", name + " Active", 0, 1, i == 1 ? 1 : 0, Boolean);
        addParameter(id + "voices", name + " Voices", 0, 8, 8, Integer);
        addParameter(id + "semitones", name + " Semitones", -24, 24, 0, Integer);
        addParameterModulate(id + "cents", name + " Fine", -100, 100, 0, Integer);
        addParameterModulate(id + "level", name + " Volume", 0.0f, 1.0f, 0.8f, Float);
        addParameterModulate(id + "panning", name + " Pan", 0.0f, 1.0f, 0.5f, Float);
        addParameterModulate(id + "detune_amount", name + " Detune Amount", 0.0f, 1.0f, 0, Float);
        addParameterModulate(id + "detune_dense", name + " Detune Dense", 0.0f, 1.0f, 0, Float);
        addParameter(id + "detune_mode", name + " Detune Mode", 1, 2, 1, Integer);
        addParameterModulate(id + "phase", name + " Phase offset", 0, 1, 0, Float);
        addParameter(id + "random_phase", name + " Random Phase", 0, 1, 0, Boolean);
        addParameterModulate(id + "stereo", name + " Stereo Wideness", 0, 200, 0, Float);
        // Envelope Part
        addParameter(id + "attack", name + " Attack", 0, 2, 0.01, Float);
        addParameter(id + "decay", name + " Attack", 0, 2, 0.01, Float);
        addParameter(id + "sustain", name + " Attack", 0, 2, 0.01, Float);
        addParameter(id + "release", name + " Attack", 0, 2, 0.01, Float);

        // Waveform
        addParameter(id + "waveform", name + " Waveform", 1, 9, 3, Integer);
        addParameterModulate(id + "waveform_mix", name + " Waveform Mix", 0, 1, 0, Float);
    }

    // FX SERIES LATER!
}