//
// Created by versustune on 13.06.20.
//

#ifndef VENO_MODULATEVALUE_H
#define VENO_MODULATEVALUE_H

#include <string>
#include "JuceHeader.h"

// a class that is used to can handle the value from a "gui-part" and the matrix and all other modulation
class ModulateValue
{
public:
    ModulateValue (const std::string& name, const std::string& processId);
    ~ModulateValue ();
    void addValue (float d);
    void setBaseValue(float base);
    void set(float value, float max, float min);
private:
    std::string m_name;
    std::string m_processId;
    float m_value = 0;
    float m_baseValue = 0;
    float m_maxValue = 1;
    float m_minValue = -1;
    JUCE_LEAK_DETECTOR(ModulateValue)
};
#endif //VENO_MODULATEVALUE_H
