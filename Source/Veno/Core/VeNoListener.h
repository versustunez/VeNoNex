#ifndef VENO_VENOLISTENER_H
#define VENO_VENOLISTENER_H


#include <string>
#include "JuceHeader.h"

class VeNoListener
{
public:
    virtual ~VeNoListener() = default;
    virtual void parameterChanged(const std::string& parameterID, const std::string& translation, float newValue) = 0;
    virtual void notify(const std::string& name, float value) = 0;
private:
    JUCE_LEAK_DETECTOR(VeNoListener)
};


#endif //VENO_VENOLISTENER_H
