#include "VeNoParameterStringHelper.h"

std::string VeNoParameterStringHelper::osc1 = "osc1";
std::string VeNoParameterStringHelper::osc2 = "osc2";
std::string VeNoParameterStringHelper::osc3 = "osc3";
std::string VeNoParameterStringHelper::osc4 = "osc4";

VeNoParameterStringHelper::VeNoParameterStringHelper ()
{
    initBaseCaches ();
    initOscillatorCaches ();
}

void VeNoParameterStringHelper::initOscillatorCaches ()
{
    for (int i = 0; i < 4; ++i)
    {
        std::string osc = "osc" + std::to_string (i + 1) + "__";
        auto& container = getRealContainer (i);
        container.emplace_back (osc + "active");
        container.emplace_back (osc + "voices");
        container.emplace_back (osc + "semitones");
        container.emplace_back (osc + "cents");
        container.emplace_back (osc + "level");
        container.emplace_back (osc + "panning");
        container.emplace_back (osc + "detune_amount");
        container.emplace_back (osc + "detune_dense");
        container.emplace_back (osc + "detune_mode");
        container.emplace_back (osc + "phase");
        container.emplace_back (osc + "random_phase");
        container.emplace_back (osc + "stereo");
        container.emplace_back (osc + "attack");
        container.emplace_back (osc + "decay");
        container.emplace_back (osc + "sustain");
        container.emplace_back (osc + "release");
        container.emplace_back (osc + "waveform_base");
        container.emplace_back (osc + "waveform");
        container.emplace_back (osc + "waveform_mix");
    }
}

void VeNoParameterStringHelper::initBaseCaches ()
{
    baseStrings.emplace_back ("master__volume");
    baseStrings.emplace_back ("pitch__wheel");
    baseStrings.emplace_back ("pitchbend__up");
    baseStrings.emplace_back ("pitchbend__down");
}

std::string& VeNoParameterStringHelper::getForOscillator (std::string& name, int index)
{
    if (name == osc1)
    {
        return getInstance ().oscillatorOne[index];
    }
    if (name == osc2)
    {
        return getInstance ().oscillatorTwo[index];
    }
    if (name == osc3)
    {
        return getInstance ().oscillatorThree[index];
    }
    if (name == osc4)
    {
        return getInstance ().oscillatorFour[index];
    }
    return name;
}

std::string& VeNoParameterStringHelper::getBase (int index)
{
    return getInstance ().baseStrings[index];
}

std::vector<std::string>& VeNoParameterStringHelper::getRealContainer (int index)
{
    switch (index)
    {
        case 1:
            return oscillatorTwo;
        case 2:
            return oscillatorThree;
        case 3:
            return oscillatorFour;
        default:
            return oscillatorOne;
    }
}
