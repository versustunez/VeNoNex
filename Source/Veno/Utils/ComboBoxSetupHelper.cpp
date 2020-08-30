#include "ComboBoxSetupHelper.h"

void ComboBoxSetupHelper::setupWaveTable (VeNoSelect& box)
{
    box.addItem ("Saw");
    box.addItem ("Sine");
    box.addItem ("Square");
    box.addItem ("Triangle");
    box.addItem ("Dirty Saw");
    box.addItem ("Dirty Square");
    box.addItem ("Synth 1");
    box.addItem ("Synth 2");
    box.addItem ("VeNoX");
}

void ComboBoxSetupHelper::setupFilter (VeNoSelect& box)
{
    box.addItem ("NO");
    box.addItem ("LowPass");
    box.addItem ("HighPass");
}

void ComboBoxSetupHelper::setup (VeNoSelect& box, VeNoSelect::Type type)
{
    switch (type)
    {
        case VeNoSelect::Type::WaveTable:
            setupWaveTable (box);
            break;
        case VeNoSelect::Type::Filter:
            setupFilter (box);
            break;
        default:
            break;
    }
}
