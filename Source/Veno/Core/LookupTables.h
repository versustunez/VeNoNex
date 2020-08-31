#ifndef VENO_LOOKUPTABLES_H
#define VENO_LOOKUPTABLES_H

#include "JuceHeader.h"

class LookupTables
{
public:
    static double freqLookup[128];
    static double detuneLookup[9];
    static double preCalculatedMidiNotes[128];

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LookupTables)
};

#endif //VENO_LOOKUPTABLES_H
