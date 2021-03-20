#ifndef VENO_DETUNEHELPER_H
#define VENO_DETUNEHELPER_H


#include <string>
#include "../../../Core/ParameterHandler.h"
#include "DetuneAlgos/DetuneLookup.h"
#include "OscillatorParameters.h"

class DetuneHelper
{
private:
    std::string m_name;
    std::shared_ptr<OscillatorParameters> m_parameters;
public:
    int m_mode = 0;
    DetuneLookup* m_detuneAlgos[3];
    DetuneHelper (const std::string& name, std::shared_ptr<OscillatorParameters>& handler, int voiceCount);

    ~DetuneHelper ();

    void update (double freq, int midiNote);

    void setMode ();

    DetuneLookup* getDetune ();
};


#endif //VENO_DETUNEHELPER_H
