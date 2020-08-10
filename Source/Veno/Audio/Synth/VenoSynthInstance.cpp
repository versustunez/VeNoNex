//
// Created by Maurice on 26.09.2019.
//

#include "VenoSynthInstance.h"

#include <utility>

VenoSynthInstance::VenoSynthInstance(double sampleRate)
{
    // this vibrato is not needed! because it should handled via matrix later
    vibrato = new VenoLFO();
    for (int i = 0; i < count; i++)
    {
        oscillators[i] = new VenoOscillator(vibrato);
        oscillators[i]->name = "osc" + std::to_string(i);
        envelopes[i] = new VenoEnvelope(sampleRate);
        envelopes[i]->name = "osc" + std::to_string(i);
        oscillators[i]->setup();
        if (i == 0)
        {
            oscillators[i]->setActive(true);
        }
    }
    isInit = true;
}

VenoSynthInstance::~VenoSynthInstance()
{
    delete oscillators[0];
    delete oscillators[1];
    delete oscillators[2];
    delete oscillators[3];
    delete envelopes[0];
    delete envelopes[1];
    delete envelopes[2];
    delete envelopes[3];
    delete lfos[0];
    delete lfos[1];
    delete vibrato;
    // VenoSynthInstance::chain = nullptr;
}
void VenoSynthInstance::updateSampleRate()
{
    float sRate = AudioConfig::getInstance()->getSampleRate();
    if (lastSampleRate != sRate)
    {
        lastSampleRate = sRate;
        for (int i = 0; i < count; i++)
        {
            envelopes[i]->setSampleRate(lastSampleRate);
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
