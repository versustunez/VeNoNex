//
// Created by maurice on 26.09.19.
//

#ifndef VENO_VENOVOICE_H
#define VENO_VENOVOICE_H

#include "../../../../JuceLibraryCode/JuceHeader.h"
#include "VenoSynthInstance.h"

class VenoVoice : public SynthesiserVoice {
public:
	int index = 0;
	VenoVoice(int _index, double sampleRate);
	~VenoVoice();
	// Geerbt über SynthesiserVoice
	bool canPlaySound(SynthesiserSound*) override;
	void startNote(int midiNoteNumber, float velocity, SynthesiserSound* sound, int currentPitchWheelPosition) override;
	void stopNote(float velocity, bool allowTailOff) override;
	void pitchWheelMoved(int newPitchWheelValue) override;
	void controllerMoved(int controllerNumber, int newControllerValue) override;
	void renderNextBlock(AudioBuffer<float>& outputBuffer, int startSample, int numSamples) override;

  VenoSynthInstance * getSynth();

private:
	VenoSynthInstance *synth;
	float velocity = 0.0;
	bool playSound = true;
};


#endif //VENO_VENOVOICE_H
