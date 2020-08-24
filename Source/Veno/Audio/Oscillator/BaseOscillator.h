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
private:
    std::string m_id;
    std::string m_name;
    std::vector<OscillatorVoice*> m_voices;
    ParameterHandler* m_handler = nullptr;
    int m_maxVoices = 9;
    float m_freq = 0.0;
    int m_midiNote = 0;
    bool m_hasDetune = true;
    std::vector<float> m_values{0, 0, 0};
    std::vector<float> m_panning{0, 0};
    std::shared_ptr<WaveTableWrapper> m_waveTableHelper;
    std::shared_ptr<DetuneHelper> m_DetuneHelper;
    std::shared_ptr<OscillatorParameters> m_parameters;
public:
    BaseOscillator(const std::string& id, const std::string& name, int maxVoices);
    ~BaseOscillator();
    bool start(int currentMidiNote);
    void stop();
    bool render();
    bool applyModules();
    void initModules();
    void setFrequency();

    // getter
    const std::vector<float>& getValue();
    float getLeftValue();
    float getRightValue();
    float getMonoValue();

    float getPitchBend();
protected:
    //modules
    std::shared_ptr<Widener> m_widener;
    std::shared_ptr<Limiter> m_limiter;
};


#endif //VENO_BASEOSCILLATOR_H
