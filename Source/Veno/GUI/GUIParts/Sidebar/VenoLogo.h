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
protected:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (VenoLogo)
};
#endif //VENO_VENOLOGO_H
