#include "DetuneLookup.h"
#include "../../Utils.h"
#include "../../Core/LookupTables.h"

// @todo add support for multi Unison algos!
void DetuneLookup::setNewLookup(float freq, int voices, float detune, float detuneDensity, int midiNote)
{
    if (lookupTable.empty()
        || lastMidiNote != midiNote
        || lastDetune != detune
        || voices != lastVoices) {
        // calculate Detune :)
        auto real = voices + 1;
        lookupTable.resize(real);
        auto half = voices / 2;
        auto halfReal = real / 2;
        auto centPlus = (getRealDetune(detune) *  LookupTables::preCalculatedMidiNotes[lastMidiNote]) / real;
        auto cents = 0;
        int venoCount = 1;
        for (int i = 0; i < real; ++i) {
            if (i == half) {
                venoCount = 1;
                lookupTable[i] = 1;
                continue;
            }
            if (detune == 0) {
                lookupTable[i] = 1;
                continue;
            }
            auto pos = venoCount / halfReal;
            cents += centPlus + (centPlus * (pos * pos * pos));
            if(i % 2 == 0) {
                lookupTable[i] = 1 - (VeNo::Utils::centsToRatio(cents) - 1);
            } else {
                lookupTable[i] = (VeNo::Utils::centsToRatio(cents));
            }
            venoCount++;
        }
        lastDetune = detune;
        lastVoices = voices;
    }
    lastMidiNote = midiNote;
    lastFreq = freq;
}
float DetuneLookup::getRealDetune(float detune)
{
    if (detune != lastDetune) {
        float d = detune / 600;
        lastRealDetune = (d * d * d * d) * 900;
    }
    return lastRealDetune;
}

float DetuneLookup::getCalculatedDetune(int voice)
{
    float freq = lastFreq * lookupTable[voice];
    return freq;
}
