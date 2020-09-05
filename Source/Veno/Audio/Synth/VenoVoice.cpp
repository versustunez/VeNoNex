#include "VenoVoice.h"
#include "VenoSound.h"
#include "JuceHeader.h"
#include "../../VenoInstance.h"

VenoVoice::VenoVoice (int _index, double sampleRate, const std::string& id)
        : m_index (_index), m_id (id)
{
    m_synth = new VenoSynthInstance (id, sampleRate, m_index);
}

VenoVoice::~VenoVoice ()
{
    delete m_synth;
}

//make sure it's can only play sound if the voice count is >= the current voice index
//so we can make sure that we can create mono-legato sounds
bool VenoVoice::canPlaySound (SynthesiserSound* sound)
{
    return (m_synth->isInit && playSound && dynamic_cast<VenoSound*> (sound) != nullptr);
}

void VenoVoice::startNote (int midiNoteNumber, float velocity, SynthesiserSound* sound, int currentPitchWheelPosition)
{
    VenoVoice::velocity = velocity;
    int count = m_synth->count;
    for (int i = 0; i < count; i++)
    {
        m_synth->getOscillator (i)->start (midiNoteNumber);
        m_synth->getEnvelope (i)->prepare ();
        m_synth->getEnvelope (i)->noteOn ();
    }

}

void VenoVoice::stopNote (float velocity, bool allowTailOff)
{
    int count = m_synth->count;
    for (int i = 0; i < count; i++)
    {
        VeNoEnvelope* env = m_synth->getEnvelope (i);
        env->noteOff ();
        if (!env->isActive () || velocity == 0)
        {
            m_synth->getOscillator (i)->stop ();
            clearCurrentNote ();
            VenoVoice::velocity = velocity;
        }
    }
}

void VenoVoice::pitchWheelMoved (int newPitchWheelValue)
{
    double realValue = (((double) newPitchWheelValue / 16383) * 2) - 1;
    VenoInstance::getInstance (m_id)->handler->setParameterValue ("pitch__wheel", realValue);
}

void VenoVoice::controllerMoved (int controllerNumber, int newControllerValue)
{
}

void VenoVoice::renderNextBlock (AudioBuffer<float>& outputBuffer, int startSample, int numSamples)
{
    m_synth->updateSampleRate (); // is not heavy alot of the time!
    int count = m_synth->count;
    while (--numSamples >= 0)
    {
        double output[3] = {0, 0, 0};
        bool cleanNote = true;
        bool runIntoSample = false;
        for (int i = 0; i < count; i++)
        {
            SynthOscillator* osc = m_synth->getOscillator (i);
            VeNoEnvelope* env = m_synth->getEnvelope (i);
            if (osc == nullptr || env == nullptr)
            {
                continue;
            }
            if (env->isActive ())
            {
                cleanNote = false;
                env->update ();
                auto envValue = env->getValue ();
                bool status = osc->render ();
                if (status)
                {
                    runIntoSample = true;
                    output[0] += osc->getMonoValue () * envValue;
                    output[1] += osc->getLeftValue () * envValue;
                    output[2] += osc->getRightValue () * envValue;
                }
            }
        }

        if (cleanNote || !runIntoSample)
        {
            clearCurrentNote ();
        }

        int channelCount = outputBuffer.getNumChannels ();
        if (channelCount == 1)
        {
            output[0] *= 0.25;
            outputBuffer.addSample (0, startSample, output[0]);
        }
        else
        {
            output[1] *= 0.25;
            output[2] *= 0.25;
            outputBuffer.addSample (0, startSample, output[1]);
            outputBuffer.addSample (1, startSample, output[2]);
        }
        ++startSample;
    }
    /* if (m_synth->getChain() != nullptr) {
        m_synth->getChain()->render(outputBuffer);
    }*/
}

VenoSynthInstance* VenoVoice::getSynth ()
{
    return m_synth;
}
