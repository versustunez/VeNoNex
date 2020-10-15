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

    void setFrequency (double frequency, int midiNote);

    virtual void prepareDetune (int voices) = 0;

    double getDetuneFreq (int index);

    std::vector<double> m_lookup;
    double m_frequency = 0;
    int m_size;
protected:
    double m_lastDetune = 0;
    int m_lastVoices = 0;
    std::shared_ptr<OscillatorParameters> m_parameters;
    double m_currentDetune = 0; //can calcucated by a special function
    std::string m_name;
    double m_detuneCents;
    int m_midiNote = 0;
};


#endif //VENO_DETUNELOOKUP_H
