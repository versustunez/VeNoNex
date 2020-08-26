#ifndef VENO_VENOVOICE_H
#define VENO_VENOVOICE_H

#include "../../../../JuceLibraryCode/JuceHeader.h"
#include "VenoSynthInstance.h"

class VenoVoice : public SynthesiserVoice
{
public:
    int m_index = 0;

    VenoVoice (int _index, double sampleRate, const std::string& id);

    ~VenoVoice () override;

    // Geerbt über SynthesiserVoice
    bool canPlaySound (SynthesiserSound*) override;

    void
    startNote (int midiNoteNumber, float velocity, SynthesiserSound* sound, int currentPitchWheelPosition) override;

    void stopNote (float velocity, bool allowTailOff) override;

    void pitchWheelMoved (int newPitchWheelValue) override;

    void controllerMoved (int controllerNumber, int newControllerValue) override;

    void renderNextBlock (AudioBuffer<float>& outputBuffer, int startSample, int numSamples) override;

    VenoSynthInstance* getSynth ();

private:
    VenoSynthInstance* m_synth;
    float velocity = 0.0;
    bool playSound = true;
    std::string m_id;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (VenoVoice)
};


#endif //VENO_VENOVOICE_H
