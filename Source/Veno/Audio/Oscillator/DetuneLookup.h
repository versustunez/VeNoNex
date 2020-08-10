#ifndef VENO_DETUNELOOKUP_H
#define VENO_DETUNELOOKUP_H

#include <iostream>
#include <vector>
class DetuneLookup {
public:
    float getCalculatedDetune(int voice);
    void setNewLookup(float freq, int voices, float detune, float detuneDensity, int midiNote);

protected:
    float getRealDetune(float detune);

private:
    int lastMidiNote = 0;
    float lastRealDetune = 0;
    float lastDetune = 0;
    float lastFreq = 0;
    int lastVoices = 0;
    //helper.py has a value to do that!
    std::vector<float> lookupTable = {};
};

#endif //VENO_DETUNELOOKUP_H
