#include "VenoSynthInstance.h"
#include "../../Core/AudioConfig.h"
#include "../Oscillator/SynthOscillator.h"

#include <utility>

VenoSynthInstance::VenoSynthInstance (const std::string& id, double sampleRate)
{
    m_id = id;
    // this vibrato is not needed! because it should handled via matrix later
    for (int i = 0; i < count; i++)
    {
        auto name = "osc" + std::to_string (i + 1);
        oscillators[i] = new SynthOscillator (id, 9, name);
        envelopes[i] = new VenoEnvelope (id, name, sampleRate);
    }
    isInit = true;
}

VenoSynthInstance::~VenoSynthInstance ()
{
    delete oscillators[0];
    delete oscillators[1];
    delete oscillators[2];
    delete oscillators[3];
    delete envelopes[0];
    delete envelopes[1];
    delete envelopes[2];
    delete envelopes[3];
    // VenoSynthInstance::chain = nullptr;
}

void VenoSynthInstance::updateSampleRate ()
{
    float sRate = AudioConfig::getInstance ()->getSampleRate ();
    if (lastSampleRate != sRate)
    {
        lastSampleRate = sRate;
        for (int i = 0; i < count; i++)
        {
            envelopes[i]->setSampleRate (lastSampleRate);
        }
    }
}

/* void VenoSynthInstance::setChain(std::shared_ptr<Chain>& chainModule) {
    VenoSynthInstance::chain = chainModule;
}

std::shared_ptr<Chain> VenoSynthInstance::getChain() {
    return chain;
}
*/
