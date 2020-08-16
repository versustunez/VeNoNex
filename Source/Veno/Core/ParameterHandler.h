#ifndef VENO_PARAMETERHANDLER_H
#define VENO_PARAMETERHANDLER_H

#include "JuceHeader.h"
#include <unordered_map>
#include "VeNoListener.h"

enum ParameterTypes {
    Integer = 0,
    Float,
    Boolean
};
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
    void registerListener(const std::string& name, VeNoListener* listener);
    void deleteListener(const std::string& name);
    void parameterChanged(const String& parameterID, float newValue) override;
protected:
private:
    std::string m_id;
    std::vector<std::unique_ptr<RangedAudioParameter>> m_params;
    std::unordered_map<std::string, std::string> m_paramNames;
    std::unordered_map<std::string, VeNoListener*> m_listener;
    JUCE_LEAK_DETECTOR (ParameterHandler)
};


#endif //VENO_PARAMETERHANDLER_H
