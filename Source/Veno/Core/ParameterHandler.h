#ifndef VENO_PARAMETERHANDLER_H
#define VENO_PARAMETERHANDLER_H

#include "JuceHeader.h"
#include <unordered_map>
#include "VeNoListener.h"
#include "../Audio/Engine/VeNoParameter.h"

class ParameterHandler :  public AudioProcessorValueTreeState::Listener
{
public:
    explicit ParameterHandler(const std::string& id);
    ~ParameterHandler() override;
    void setupParameter();
    AudioProcessorValueTreeState::ParameterLayout setupProcessor();
    void addParameter(const std::string& name, const std::string& showName, float min, float max, float value, ParameterTypes type);
    void addParameterModulate(const std::string& name, const std::string& showName, float min, float max, float value, ParameterTypes type);
    void initParameterForListener(AudioProcessorValueTreeState* state);
    void parameterChanged(const String& parameterID, float newValue) override;
    VeNoParameter* getParameter(const std::string& name);
    float getParameterValue(const std::string& name);
    float getParameterValue(const std::string& name, float defaultValue);
    void setParameterValue(const std::string& parameterId, float value);
protected:
private:
    std::string m_id;
    std::vector<std::unique_ptr<RangedAudioParameter>> m_params;
    std::unordered_map<std::string, VeNoParameter*> m_parameters;
    std::unordered_map<std::string, VeNoListener*> m_listener;
    JUCE_LEAK_DETECTOR (ParameterHandler)
};


#endif //VENO_PARAMETERHANDLER_H
