#ifndef VENO_COMBOBOXSETUPHELPER_H
#define VENO_COMBOBOXSETUPHELPER_H


#include "JuceHeader.h"
#include "../GUI/Components/Base/VeNoSelect.h"

class ComboBoxSetupHelper
{
public:

    static void setup (VeNoSelect& box, VeNoSelect::Type type);

    static void setupWaveTable (VeNoSelect& box);

    static void setupFilter (VeNoSelect& box);

    static void setupDetuneModes (VeNoSelect& box);

    static void setupLimiters (VeNoSelect& box);
};


#endif //VENO_COMBOBOXSETUPHELPER_H
