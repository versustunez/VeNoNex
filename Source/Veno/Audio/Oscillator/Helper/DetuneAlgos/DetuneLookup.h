#ifndef VENO_DETUNELOOKUP_H
#define VENO_DETUNELOOKUP_H


#include <vector>
#include "../../../../Core/ParameterHandler.h"
#include "../OscillatorParameters.h"

class DetuneLookup
{
// maybe later via parameter?
public:
    explicit DetuneLookup (int maxSize, std::shared_ptr<OscillatorParameters>& parameters, std::string name);

    virtual ~DetuneLookup () = default;

    void setFrequency (float frequency, int midiNote);

    virtual void prepareDetune (int voices) = 0;

    float getDetuneFreq (int index);

protected:
    int m_size;
    std::vector<float> m_lookup;
    float m_lastDetune = 0;
    int m_lastVoices = 0;
    float m_frequency = 0;
    std::shared_ptr<OscillatorParameters> m_parameters;
    float m_currentDetune = 0; //can calcucated by a special function
    std::string m_name;
    float m_detuneCents = 200.0f;
    int m_midiNote = 0;
};


#endif //VENO_DETUNELOOKUP_H
