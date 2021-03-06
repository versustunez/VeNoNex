#ifndef VENO_SYNTHOSCILLATOR_H
#define VENO_SYNTHOSCILLATOR_H

#include "JuceHeader.h"
#include "../Engine/Modulator.h"
#include "BaseOscillator.h"

class SynthOscillator : public Modulator,
                        public BaseOscillator
{
private:
public:
    explicit SynthOscillator (const std::string& id, int maxVoices, const std::string& name);

    ~SynthOscillator ();

    float getValue () override;

    void update () override;

protected:
};


#endif //VENO_SYNTHOSCILLATOR_H
