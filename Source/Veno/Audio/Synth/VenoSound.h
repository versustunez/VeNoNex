#ifndef VENO_VENOSOUND_H
#define VENO_VENOSOUND_H

#include "JuceHeader.h"

class VenoSound : public SynthesiserSound
{
public:
    virtual bool appliesToNote (int midiNoteNumber) override;

    virtual bool appliesToChannel (int midiChannel) override;

private:
protected:
};


#endif //VENO_VENOSOUND_H
