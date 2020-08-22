#include <cmath>
#include "../../Core/LookupTables.h"
#include "VenoOscillator.h"

#define PI 3.141592653589793238462643383

void VenoOscillator::setup() {
    tableHelper.setWaveTable(waveForm);
}

void VenoOscillator::start(int currentMidiNote) {
    if (!active) {
        return;
    }
    midiNote = currentMidiNote;
    tableHelper.setWaveTable(waveForm);

    tableHelper.setFreq(getFrequencyFromMidiNote(), voices, detune, detuneDensity, midiNote);
    //re-trigger oscillator from start phase else move with the flow
    if (reTrigger) {
        tableHelper.reset();
    }
}

//function that will stop the osc
void VenoOscillator::stop() {
    output[0] = 0;
    output[1] = 0;
    output[2] = 0;
    midiNote = 0;
}

bool VenoOscillator::render() {
    if (!active || midiNote < 1) {
        return false;
    }
    float freq = getFrequencyFromMidiNote();

    if (vibratoModule.isActive) {
        auto vibratoStrength = (midiNote / 127);
        // if detune is on. apply 0.2 extra to vibrato...
        if (voices > 0 && detune > 0 && detuneDensity > 0) {
            vibratoStrength += 0.2;
        }
        freq = freq - (freq * vibratoModule.apply(vibratoStrength));
    }
    tableHelper.setFreq(
            std::abs(freq),
            voices,
            detune, detuneDensity,
            midiNote
    );
    int baseVoice = tableHelper.currentMainVoice; //center voice...
    output[0] = tableHelper.getOutput(baseVoice) * 0.75;
    panned[0] = 0;
    panned[1] = 0;
    tableHelper.updatePhase(baseVoice);
    float detuneOutput = 0.0;
    if (voices > 0) {
        int length = voices * 2 + 1;
        bool leftPanning = true;
        for (int i = 0; i < length; ++i) {
            if (i == tableHelper.currentMainVoice) {
                leftPanning = false;
                continue;
            }
            float tableOutput = tableHelper.getOutput(i);
            detuneOutput += tableOutput;
            if (leftPanning) {
                panned[0] = tableOutput * widenessModule.getDetuneWideness();
            } else {
                panned[1] = tableOutput * widenessModule.getDetuneWideness();
            }
            tableHelper.updatePhase(i);
        }
        detuneOutput /= (float) voices;
        detuneOutput *= detuneDensity;
        output[0] += detuneOutput;
    }
    output[0] *= level;
    panned[0] *= level;
    panned[1] *= level;
    widenessModule.apply(output);
    applyPanning();
    limiterModule.apply(output);
    filter.apply(output);

    return true;
}

void VenoOscillator::setVoices(int voiceCount) {
    if (voiceCount > maxVoices) {
        voiceCount = maxVoices;
    }
    if (voiceCount < 0) {
        voiceCount = 0;
    }
    voices = voiceCount;
    if (voices > 0) {
        tableHelper.currentMainVoice = voices + 1;
    } else {
        tableHelper.currentMainVoice = 0;
    }
}

//we apply our detune now to the midiNote
float VenoOscillator::getFrequencyFromMidiNote() {
    float midi = this->midiNote;
    midi += semitonesShift;
    if (midi < 1) {
        midi = 1; //play no note if the note is less then 1
    } else if (midi > 127) {
        midi = 127;
    }
    // the lookup will only work if no half notes are applied...
    if (pitchBend == 0) {
        return LookupTables::freqLookup[(int) midi];
    }

    midi += (pitchBend / 100);
    if (midi < 1) {
        midi = 1;
    } else if (midi > 128) {
        midi = 128;
    }
    return std::exp((midi - 69) * std::log(2) / 12) * 440.0f;
    //original formel => std::exp((midi - 69) * std::log(2) / 12) * 440;
}

//Wavetables are one Octave to high!
void VenoOscillator::setSemitonesShift(int semitonesShift) {
    VenoOscillator::semitonesShift = semitonesShift;
}

void VenoOscillator::setPanning(float _panning) {
    float angle = _panning * PI_4;
    VenoOscillator::panning[0] = SQRT2_2 * double(std::cos(angle) - std::sin(angle));
    VenoOscillator::panning[1] = SQRT2_2 * double(std::cos(angle) + std::sin(angle));
}

void VenoOscillator::setReTrigger(bool reTrigger) {
    VenoOscillator::reTrigger = reTrigger;
}

void VenoOscillator::setLevel(float level) {
    VenoOscillator::level = level;
}

void VenoOscillator::setWaveForm(int _waveForm) {
    if (_waveForm < 0) {
        _waveForm = 0;
    }
    tableHelper.setWaveTable(_waveForm);
}

void VenoOscillator::setDetune(float detune) {
    if (detune != prevDetune) {
        prevDetune = detune;
        VenoOscillator::detune = detune;
    }
}

VenoOscillator::VenoOscillator(VenoLFO *vibrato) {
    vibratoModule.lfo = vibrato;
}

void VenoOscillator::setPitchBend(float _pitchBend) {
    //get pitch bend range!
    if (_pitchBend == 0) {
        pitchBend = 0;
    } else if (_pitchBend < 0) {
        pitchBend = pitchBendRange[1] * _pitchBend;
    } else {
        pitchBend = pitchBendRange[0] * _pitchBend;
    }
    pitchBend *= 100;
}

void VenoOscillator::setPitchBendRange(int up, int down) {
    pitchBendRange[0] = up;
    pitchBendRange[1] = down;
}

void VenoOscillator::setPitchBendRangeUp(int up) {
    pitchBendRange[0] = up;
}

void VenoOscillator::setPitchBendRangeDown(int down) {
    pitchBendRange[1] = down;
}

// for the Oscillator this functions is doing nothing because it only should render if needed!
void VenoOscillator::update()
{
}

#undef PI
