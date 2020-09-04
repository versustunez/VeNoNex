#ifndef VENO_VENOPARAMETER_H
#define VENO_VENOPARAMETER_H

#include <string>
#include "ModulateValue.h"

enum ParameterTypes
{
    Integer = 0,
    Float,
    Boolean
};

class VeNoParameter
{
private:
    std::string m_name;
    std::string m_showName;
    std::string m_id;
    double m_value;
    double m_max;
    double m_min;
    bool m_isModulation = false;
    std::shared_ptr<ModulateValue> m_modulateValue;
public:
    VeNoParameter (const std::string& name, const std::string& shownName, double min, double max, double value,
                   const std::string& id);

    ~VeNoParameter ();

    void createModulationValue ();

    std::unique_ptr<RangedAudioParameter> createParameter (ParameterTypes type);

    void setValue (double value);

    double getValue ();
    double getValueForVoice (int voice);

    double getBaseValue ();

    bool getAsBoolean ();

    int getAsInt ();

    std::string getShowName ();

    std::shared_ptr<ModulateValue> getModulateValue ();

    double getMaxValue() const;
    double getMinValue() const;
};


#endif //VENO_VENOPARAMETER_H
