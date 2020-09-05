#ifndef VENO_BASEOSCILLATOR_H
#define VENO_BASEOSCILLATOR_H


#include <string>
#include "Modules/OscillatorVoice.h"
#include "../../Core/ParameterHandler.h"
#include "Helper/WaveTableWrapper.h"
#include "Modules/Limiter.h"
#include "Helper/OscillatorParameters.h"

class BaseOscillator
{
protected:
    std::string m_id;
    std::string m_name;
    ParameterHandler* m_handler = nullptr;
    int m_maxVoices = 9;
    bool m_hasDetune = true;
    int m_index = 0;
public:
    BaseOscillator (const std::string& id, const std::string& name, int maxVoices);

    ~BaseOscillator ();

    bool start (int currentMidiNote);

    void stop ();

    virtual bool render ();

    bool postProcessing ();

    bool preProcessing ();

    bool processVoices (int i);

    void initModules ();

    void setFrequency ();

    // getter
    const std::vector<double>& getValue ();

    double getLeftValue ();

    double getRightValue ();

    double getMonoValue ();

    double getPitchBend ();

    void setIndex (int index);

protected:
    double m_freq = 0.0;
    int m_midiNote = 0;
    std::vector<OscillatorVoice*> m_voices;
    std::shared_ptr<WaveTableWrapper> m_waveTableHelper;
    std::shared_ptr<DetuneHelper> m_DetuneHelper;
    std::shared_ptr<OscillatorParameters> m_parameters;
    std::vector<double> m_values{0, 0, 0};
    std::vector<double> m_panning{0, 0};

    //modules
    std::shared_ptr<Widener> m_widener;
    std::shared_ptr<VeNo::Limiter> m_limiter;
};


#endif //VENO_BASEOSCILLATOR_H
