//
// Created by versustune on 14.06.20.
//

#ifndef VENO_VENOLOGO_H
#define VENO_VENOLOGO_H

#include "JuceHeader.h"

class VenoLogo
{
private:
    Image realLogo;
    static VenoLogo* instance;
public:
    static VenoLogo* getInstance ();
    static Image getLogo ();
    static void deleteInstance ();
    VenoLogo ();
    ~VenoLogo () = default;
};
#endif //VENO_VENOLOGO_H
