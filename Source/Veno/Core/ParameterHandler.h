#ifndef VENO_PARAMETERHANDLER_H
#define VENO_PARAMETERHANDLER_H

#include "JuceHeader.h"
#include <unordered_map>
#include "VeNoListener.h"
#include "../Audio/Engine/VeNoParameter.h"

class ParameterHandler : public AudioProcessorValueTreeState::Listener
{
public:
    explicit ParameterHandler (const std::string& id);

    ~ParameterHandler () override;

    void setupParameter ();

    AudioProcessorValueTreeState::ParameterLayout setupProcessor ();

    void addParameter (const std::string& name, const std::string& showName, double min, double max, double value,
                       ParameterTypes type);

    void addParameterModulate (const std::string& name, const std::string& showName, double min, double max, double value,
                               ParameterTypes type);

    void initParameterForListener (AudioProcessorValueTreeState* state);

    void parameterChanged (const String& parameterID, float newValue) override;

    VeNoParameter* getParameter (const std::string& name);

    double getParameterValue (const std::string& name);

    double getParameterValue (const std::string& name, double defaultValue);

    void setParameterValue (const std::string& parameterId, double value);

    std::shared_ptr<ModulateValue> getModulateValue (const std::string& name);

    void registerListener (const std::string& parameterId, VeNoListener* listener);

    void unregisterListener (const std::string& parameterId);

protected:
private:
    std::string m_id;
    std::vector<std::unique_ptr<RangedAudioParameter>> m_params;
    std::unordered_map<std::string, VeNoParameter*> m_parameters;
    std::unordered_map<std::string, VeNoListener*> m_listener;
    AudioProcessorValueTreeState* m_treeState;

    JUCE_LEAK_DETECTOR (ParameterHandler)
};


#endif //VENO_PARAMETERHANDLER_H
