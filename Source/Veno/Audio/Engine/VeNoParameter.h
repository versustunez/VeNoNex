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
    float m_value;
    float m_max;
    float m_min;
    bool m_isModulation = false;
    std::unique_ptr<ModulateValue> m_modulateValue;
public:
    VeNoParameter(const std::string& name, const std::string& shownName, float min, float max, float value,
                  const std::string& id);
    ~VeNoParameter();
    void createModulationValue();
    std::unique_ptr<RangedAudioParameter> createParameter(ParameterTypes type);
    void setValue(float value);
    float getValue();
    float getBaseValue();
    bool getAsBoolean();
    int getAsInt();
    std::string getShowName();
};


#endif //VENO_VENOPARAMETER_H
