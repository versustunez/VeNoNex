#ifndef VENO_VENOENVELOPE_H
#define VENO_VENOENVELOPE_H

#include "JuceHeader.h"
#include "../Engine/Modulator.h"
#include "../../Core/ParameterHandler.h"

/*
 * this is a small wrapper around JUCE ADSR with saving of the current state
 */
class VeNoEnvelope : public Modulator
{
public:
    explicit VeNoEnvelope (const std::string& id, const std::string& name, double sampleRate);

    ~VeNoEnvelope () override = default;

    void setSampleRate (double sampleRate);

    double getValue () override;

    void prepare ();

    bool isActive ();

    void noteOn ();

    void noteOff ();

    bool reTrigger = false;

    void update () override;

protected:
    ADSR::Parameters m_parameters{};
    ADSR m_adsr;
    double m_sampleRate = 44100;
    std::string m_id;
    std::string m_name;
    ParameterHandler* m_handler;
    VeNoParameter* m_attack;
    VeNoParameter* m_decay;
    VeNoParameter* m_sustain;
    VeNoParameter* m_release;
};

#endif //VENO_VENOENVELOPE_H
