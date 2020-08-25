#ifndef VENO_VENOXDETUNE_H
#define VENO_VENOXDETUNE_H


#include "DetuneLookup.h"

class VeNoXDetune : public DetuneLookup
{
public:
    VeNoXDetune (int maxSize, std::shared_ptr<OscillatorParameters>& handler, const std::string& name);

    void prepareDetune (int voices) override;

protected:
    void getRealDetune ();
};


#endif //VENO_VENOXDETUNE_H
