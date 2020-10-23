#ifndef VENO_OSCILLATORPARAMETERS_H
#define VENO_OSCILLATORPARAMETERS_H


#include "../../Engine/VeNoParameter.h"
#include "../../../Core/ParameterHandler.h"

/**
 * Dirty Wrapper that holds the Oscillator Pointers to avoid Parameter Lookups
 */
class OscillatorParameters
{
public:
    OscillatorParameters (ParameterHandler* handler, const std::string& name);

    ~OscillatorParameters () = default;

    VeNoParameter* m_pitchWheel;
    VeNoParameter* m_pitchUp;
    VeNoParameter* m_pitchDown;
    VeNoParameter* m_legato;
    VeNoParameter* m_portamento;

    //oscillator stuff
    VeNoParameter* m_active;
    VeNoParameter* m_voices;
    VeNoParameter* m_semitones;
    VeNoParameter* m_cents;
    VeNoParameter* m_level;
    VeNoParameter* m_panning;
    VeNoParameter* m_detuneAmount;
    VeNoParameter* m_detuneDense;
    VeNoParameter* m_detuneMode;
    VeNoParameter* m_phase;
    VeNoParameter* m_randomPhase;
    VeNoParameter* m_stereo;
    VeNoParameter* m_waveformPrimary;
    VeNoParameter* m_waveformSecond;
    VeNoParameter* m_waveformMix;

    std::string m_name;
    ParameterHandler* m_handler;
    int m_index = 0;
protected:
    VeNoParameter* getParameter (const std::string& name);
};


#endif //VENO_OSCILLATORPARAMETERS_H
