#ifndef VENO_FASTLOOKDETUNE_H
#define VENO_FASTLOOKDETUNE_H


#include "DetuneLookup.h"

class FastLookDetune : public DetuneLookup
{
public:
    FastLookDetune (int maxSize, std::shared_ptr<OscillatorParameters>& parameters, const std::string& name);

    void prepareDetune (int voices) override;
};


#endif //VENO_FASTLOOKDETUNE_H
