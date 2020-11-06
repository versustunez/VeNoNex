#ifndef VENO_WAVETABLEWRAPPER_H
#define VENO_WAVETABLEWRAPPER_H


#include <string>
#include "../../../Core/ParameterHandler.h"
#include "../../WaveTable/WaveTableGenerator.h"
#include "OscillatorParameters.h"
#include "DetuneHelper.h"

struct Voice
{
    double m_phasor = 0.0;
    double m_phaseInc = 0.0;
    double m_phaseOfs = 0;
    VeNo::WaveTableObject* m_baseWaveTable = nullptr;
    VeNo::WaveTableObject* m_currentWaveTable = nullptr;
};

class WaveTableWrapper
{
private:
    std::string m_name;
    std::shared_ptr<OscillatorParameters> m_parameters;
    VeNo::WaveTableGroup* m_baseWaveGroup = nullptr;
    VeNo::WaveTableGroup* m_currentWaveGroup = nullptr;
    std::vector<Voice*> m_voices;
public:
    WaveTableWrapper (const std::string& name, std::shared_ptr<OscillatorParameters>& parameters, int maxVoices);

    ~WaveTableWrapper ();

    bool prepare ();

    void setFrequency(int untilIndex, double baseFreq, std::shared_ptr<DetuneHelper>& detuneHelper);

    void setRandomPhase ();

    void reset ();

    double getOutput (int index);

    double getOutputRaw (int index, double offset);

    double getOutputPWM (int index);

    double getWaveTableValue (VeNo::WaveTableObject* table, double phase);

    double sampleRate = 44100;
protected:
};


#endif //VENO_WAVETABLEWRAPPER_H
