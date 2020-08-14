#ifndef VENO_PARAMETERHANDLER_H
#define VENO_PARAMETERHANDLER_H

#include "JuceHeader.h"

enum ParameterTypes {
    Integer = 0,
    Float,
    Boolean
};
class ParameterHandler
{
public:
    explicit ParameterHandler(const std::string& id);
    ~ParameterHandler();
    void setupParameter();
    AudioProcessorValueTreeState::ParameterLayout setupProcessor();
    void addParameter(const std::string& name, const std::string& showName, float min, float max, float value, ParameterTypes type);
    void addParameterModulate(const std::string& name, const std::string& showName, float min, float max, float value, ParameterTypes type);
protected:
private:
    std::string m_id;
    std::vector<std::unique_ptr<RangedAudioParameter>> params;
};


#endif //VENO_PARAMETERHANDLER_H
