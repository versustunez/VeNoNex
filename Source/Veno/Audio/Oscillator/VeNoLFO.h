#ifndef VENO_VENOLFO_H
#define VENO_VENOLFO_H


#include "BaseOscillator.h"
#include "../Engine/Modulator.h"

class VeNoLFO : public Modulator,
                public BaseOscillator
{
public:
    explicit VeNoLFO (const std::string& id, int maxVoices, const std::string& name);

    ~VeNoLFO () override;

    double getValue () override;

    void update () override;

protected:
    ModulateValue* m_freqRate;
};


#endif //VENO_VENOLFO_H
