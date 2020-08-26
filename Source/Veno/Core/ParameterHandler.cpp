#include "ParameterHandler.h"

#include "../VenoInstance.h"

ParameterHandler::ParameterHandler (const std::string& id)
{
    m_id = id;
}

ParameterHandler::~ParameterHandler ()
{
    DBG("Deleting Parameter Handler");
    for (auto& listener : m_listener)
    {
        delete listener.second;
    }

    for (auto& parameter : m_parameters)
    {
        delete parameter.second;
    }
    m_params.clear ();
    m_parameters.clear ();
    m_listener.clear ();
}

void
ParameterHandler::addParameter (const std::string& name, const std::string& showName, float min, float max, float value,
                                ParameterTypes type)
{
    m_parameters[name] = new VeNoParameter (name, showName, min, max, value, m_id);
    m_params.push_back (m_parameters[name]->createParameter (type));
}


AudioProcessorValueTreeState::ParameterLayout ParameterHandler::setupProcessor ()
{
    if (m_params.empty ())
    {
        setupParameter ();
    }
    return {m_params.begin (), m_params.end ()};
}

void ParameterHandler::addParameterModulate (const std::string& name, const std::string& showName, float min, float max,
                                             float value, ParameterTypes type)
{
    addParameter (name, showName, min, max, value, type);
    // no support for Boolean Modulations!
    if (type == ParameterTypes::Boolean)
    {
        return;
    }
    m_parameters[name]->createModulationValue ();
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
void ParameterHandler::setupParameter ()
{
    addParameterModulate ("master__volume", "Synth Volume", 0.0f, 1.5f, 1.0f, Float);
    addParameter ("pitch__wheel", "Pitch Wheel", -1.0f, 1.0f, 0, Float);
    addParameter ("pitchbend__up", "Pitch Bend Up", 0, 36, 12, Integer);
    addParameter ("pitchbend__down", "Pitch Bend Down", 0, 36, 12, Integer);
    for (int i = 1; i < 5; ++i)
    {
        std::string id = "osc" + std::to_string (i) + "__";
        std::string name = "OSC" + std::to_string (i);
        addParameter (id + "active", name + " Active", 0, 1, i == 1 ? 1 : 0, Boolean);
        addParameter (id + "voices", name + " Voices", 1, 9, 1, Integer);
        addParameter (id + "semitones", name + " Semitones", -24, 24, 0, Integer);
        addParameterModulate (id + "cents", name + " Fine", -100, 100, 0, Integer);
        addParameterModulate (id + "level", name + " Volume", 0.0f, 1.0f, 0.8f, Float);
        addParameterModulate (id + "panning", name + " Pan", -1.0f, 1.0f, 0, Float);
        addParameterModulate (id + "detune_amount", name + " Detune Amount", 0.0f, 1.0f, 0, Float);
        addParameterModulate (id + "detune_dense", name + " Detune Dense", 0.0f, 200.0f, 0, Float);
        addParameter (id + "detune_mode", name + " Detune Mode", 1, 3, 1, Integer);
        addParameterModulate (id + "phase", name + " Phase offset", 0, 1, 0, Float);
        addParameter (id + "random_phase", name + " Random Phase", 0, 1, 0, Boolean);
        addParameterModulate (id + "stereo", name + " Stereo Wideness", 0, 200, 0, Float);
        // Envelope Part
        addParameter (id + "attack", name + " Attack", 0, 2, 0.01, Float);
        addParameter (id + "decay", name + " Decay", 0, 2, 0, Float);
        addParameter (id + "sustain", name + " Sustain", 0, 1, 1, Float);
        addParameter (id + "release", name + " Release", 0, 2, 0.01, Float);

        // Waveform
        addParameter (id + "waveform_base", name + " Base Waveform", 1, 9, 3, Integer);
        addParameter (id + "waveform", name + " Waveform", 1, 9, 3, Integer);
        addParameterModulate (id + "waveform_mix", name + " Waveform Mix", 0, 1, 0, Float);
    }
    // FX SERIES LATER!
    DBG("PARAMS REGISTERED");
}

void ParameterHandler::parameterChanged (const String& parameterID, float newValue)
{
    std::string value = parameterID.toStdString ();
    m_parameters[value]->setValue (newValue);
    for (const auto& element : m_listener)
    {
        element.second->parameterChanged (m_parameters[value]);
    }
}

void ParameterHandler::initParameterForListener (AudioProcessorValueTreeState* state)
{
    if (m_parameters.empty ())
    {
        DBG("NO PARAMS REGISTER");
    }
    for (auto& m_param : m_parameters)
    {
        state->addParameterListener (m_param.first, this);
    }
}

VeNoParameter* ParameterHandler::getParameter (const std::string& name)
{
    return m_parameters[name];
}

float ParameterHandler::getParameterValue (const std::string& name)
{
    return getParameterValue (name, 0);
}

float ParameterHandler::getParameterValue (const std::string& name, float defaultValue)
{
    auto param = m_parameters[name];
    if (param != nullptr)
    {
        return param->getValue ();
    }
    return defaultValue;
}

void ParameterHandler::setParameterValue (const std::string& parameterId, float value)
{
    if (m_parameters.find (parameterId) != m_parameters.end ())
    {
        return m_parameters[parameterId]->setValue (value);
    }
}

std::shared_ptr<ModulateValue> ParameterHandler::getModulateValue (const std::string& name)
{
    return m_parameters[name]->getModulateValue();
}
