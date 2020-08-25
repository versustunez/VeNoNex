#ifndef VENO_WAVETABLEWRAPPER_H
#define VENO_WAVETABLEWRAPPER_H


#include <string>
#include "../../../Core/ParameterHandler.h"
#include "../../WaveTable/WaveTableGenerator.h"
#include "OscillatorParameters.h"

struct Voice {
    double m_phasor = 0.0;
    double m_phaseInc = 0.0;
    double m_phaseOfs = 0;
    WaveTableObject *m_baseWaveTable = nullptr;
    WaveTableObject *m_currentWaveTable = nullptr;
};

class WaveTableWrapper
{
private:
    std::string m_name;
    std::shared_ptr<OscillatorParameters> m_parameters;
    WaveTableGroup *m_baseWaveGroup = nullptr;
    WaveTableGroup *m_currentWaveGroup = nullptr;
    std::vector<Voice*> m_voices;
public:
    WaveTableWrapper(const std::string& name, std::shared_ptr<OscillatorParameters>& parameters, int maxVoices);
    ~WaveTableWrapper();
    bool prepare();
    void setFrequencyForVoice(int index, float freq);
    void setRandomPhase();
    void reset();
    // getter
    void updatePhase(int index);
    float getOutput(int index);
    float getOutputRaw(int index, float offset);
    float getOutputPWM(int index);
    float getWaveTableValue(WaveTableObject* table, float phase);

protected:
};


#endif //VENO_WAVETABLEWRAPPER_H
