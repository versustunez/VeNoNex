#ifndef VENO_SYNTHINSTANCE_H
#define VENO_SYNTHINSTANCE_H

#include <string>
#include "JuceHeader.h"

// class that hold all voices, oscillators and other stuff :)
class SynthInstance
{
private:
    std::string m_processId;
public:
    explicit SynthInstance (std::string processId);
    ~SynthInstance () = default;
protected:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SynthInstance)
};
#endif //VENO_SYNTHINSTANCE_H
