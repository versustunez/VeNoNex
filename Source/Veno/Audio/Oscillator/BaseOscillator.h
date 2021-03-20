#ifndef VENO_BASEOSCILLATOR_H
#define VENO_BASEOSCILLATOR_H


#include <string>
#include "../../Core/ParameterHandler.h"
#include "Helper/WaveTableWrapper.h"
#include "Modules/Limiter.h"
#include "Helper/OscillatorParameters.h"
#include "Modules/OscillatorFilter.h"
#include "Modules/Widener.h"

class BaseOscillator
{
protected:
    std::string m_id;
    std::string m_name;
    ParameterHandler* m_handler = nullptr;
    int m_maxVoices = 9;
    bool m_hasDetune = true;
    int m_index = 0;
    double m_lastPortamento;
public:
    BaseOscillator (const std::string& id, const std::string& name, int maxVoices);

    ~BaseOscillator ();

    bool start (int currentMidiNote, bool portamento);

    void reset();

    void stop ();

    bool render ();

    void initModules ();

    // getter
    const std::vector<double>& getValue ();

    double getLeftValue ();

    double getRightValue ();

    double getMonoValue ();

    void setIndex (int index);
    std::vector<double> m_values{0, 0, 0};
    std::shared_ptr<WaveTableWrapper> m_waveTableHelper;
protected:
    double m_freq = 0.0;
    int m_midiNote = 0;
    SmoothedValue<double, ValueSmoothingTypes::Linear> m_midiNotePortamento;
    bool m_isPorta = false;
    std::shared_ptr<DetuneHelper> m_DetuneHelper;
    std::shared_ptr<OscillatorParameters> m_parameters;
    std::vector<double> m_panning{0, 0};

    //modules
    std::shared_ptr<Widener> m_widener;
    std::shared_ptr<VeNo::Limiter> m_limiter;
    std::shared_ptr<VeNo::OscillatorFilter> m_filter;
};


#endif //VENO_BASEOSCILLATOR_H
