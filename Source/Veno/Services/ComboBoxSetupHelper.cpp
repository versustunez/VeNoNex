#include "ComboBoxSetupHelper.h"

void ComboBoxSetupHelper::setupWaveTable (VeNoSelect& box)
{
    box.addHeader("Clean");
    box.addItem ("Saw");
    box.addItem ("Sine");
    box.addItem ("Cosine");
    box.addItem ("Square");
    box.addItem ("Triangle");

    box.addHeader("Dirty");
    box.addItem ("Saw");
    box.addItem ("Square");

    box.addHeader("Custom");
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

void ComboBoxSetupHelper::setupDetuneModes (VeNoSelect& box)
{
    box.addItem ("VeNoX");
    box.addItem ("FastLookup");
    box.addItem ("Super");
}

void ComboBoxSetupHelper::setupLimiters (VeNoSelect& box)
{
    box.addItem ("HardLimiter");
    box.addItem ("PeakReducer");
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
        case VeNoSelect::Type::DetuneMode:
            setupDetuneModes(box);
            break;
        case VeNoSelect::Type::LimiterMode:
            setupLimiters(box);
            break;
        default:
            break;
    }
}
