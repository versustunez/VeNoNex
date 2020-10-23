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

    void addValue (double d);

    void addValueForVoice(double value, int voice);

    void setBaseValue (double base);

    void set (double value, double max, double min);

    double getValue ();

    double getValueForVoice (int i);

    void resetMatrixPos();

    double m_matrixPos = 0;
    double m_matrixPosPrev = 0;
private:
    std::string m_name;
    std::string m_processId;
    double m_value = 0;
    double m_baseValue = 0;
    double m_maxValue = 1;
    double m_minValue = -1;
    double m_normalised = 0;
    std::vector<double> m_voiceValues;
    std::vector<double> m_voiceMatrix;

    JUCE_LEAK_DETECTOR(ModulateValue)
};

#endif //VENO_MODULATEVALUE_H
