//
// Created by Maurice on 18.02.2020.
//

#ifndef VENO_LOOKUPTABLES_H
#define VENO_LOOKUPTABLES_H

#include "JuceHeader.h"

class LookupTables
{
public:
    static float freqLookup[128];
    static float detuneLookup[9];
    static float preCalculatedMidiNotes[128];

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LookupTables)
};

#endif //VENO_LOOKUPTABLES_H
