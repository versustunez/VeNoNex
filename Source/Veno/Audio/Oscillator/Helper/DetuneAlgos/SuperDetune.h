#ifndef VENO_SUPERDETUNE_H
#define VENO_SUPERDETUNE_H


#include "DetuneLookup.h"

class SuperDetune : public DetuneLookup
{
public:
    SuperDetune(int maxSize, std::shared_ptr<OscillatorParameters>& parameters, const std::string& name);
    void prepareDetune(int voices) override;
    void prepareSuperLookup();
    void getRealDetune();
protected:
    std::vector<float> m_superLookup;
};


#endif //VENO_SUPERDETUNE_H
