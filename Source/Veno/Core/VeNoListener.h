#ifndef VENO_VENOLISTENER_H
#define VENO_VENOLISTENER_H


#include <string>
#include "JuceHeader.h"
#include "../Audio/Engine/VeNoParameter.h"

class VeNoListener
{
public:
    virtual ~VeNoListener() = default;
    virtual void parameterChanged(VeNoParameter* parameter) = 0;
    virtual void notify(const std::string& name, float value) = 0;
private:
    JUCE_LEAK_DETECTOR(VeNoListener)
};


#endif //VENO_VENOLISTENER_H
