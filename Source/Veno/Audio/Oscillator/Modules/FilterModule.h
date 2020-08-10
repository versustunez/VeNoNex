//
// Created by Maurice on 09.10.2019.
//

#ifndef VENO_FILTERMODULE_H
#define VENO_FILTERMODULE_H

#include <cmath>
#include "JuceHeader.h"
#include "../../../Utils.h"
#include "../../WaveTable/WaveTableGenerator.h"
#include "../../../Core/AudioConfig.h"

/**
 * Filter Module is the cutoff Filter for each oscillator.. it's not the state and which filter is used
 * pre calculate all values that are available to spend less time for calculating
 */
class VenoFilterModule {
public:

    void setFilter(float _cutoff, float _q, bool force) {
        if (_cutoff == lastCutoff && _q == q) {
            return;
        }
        _cutoff = VeNo::Utils::clamp(_cutoff, 0.001, 100) / 100;
        if (_q < 0.1) {
            _q = 0.1f;
        }
        float sampleRate = AudioConfig::getInstance()->getSampleRate();
        float maxFreq = (sampleRate / 2) - 100;
        cutoff.reset(sampleRate, 0.05f);
        cutoff.setTargetValue(_cutoff * maxFreq);
        lastCutoff = _cutoff;
        q = _q;
        updateCoefficient();
    }

    void setFilterType(int _type) {
        if (type != _type) {
            type = _type;
            updateCoefficient();
        }
    }

    void apply(float *value) {
        if (type == 0) {
            return;
        }
        if (cutoff.isSmoothing()) {
            updateCoefficient();
        }
        if (lastCutoff < 0.01) {
            value[0] = 0.00001;
            value[1] = 0.00001;
            value[2] = 0.00001;
            return;
        }
        value[0] = filter.processSingleSampleRaw(value[0]);
        value[1] = filterLeft.processSingleSampleRaw(value[1]);
        value[2] = filterRight.processSingleSampleRaw(value[2]);
    }

    int type = 0;
protected:
    void updateCoefficient() {
        float rate = AudioConfig::getInstance()->getSampleRate();
        switch (type) {
            case NO:
                return;
            case LOWPASS: {
                auto iirCoefficients = IIRCoefficients::makeLowPass(rate, cutoff.getNextValue(), q);
                filter.setCoefficients(iirCoefficients);
                filterLeft.setCoefficients(iirCoefficients);
                filterRight.setCoefficients(iirCoefficients);
                break;
            }
            case HIGHPASS: {
                auto highPass = IIRCoefficients::makeHighPass(rate, cutoff.getNextValue(), q);
                filter.setCoefficients(highPass);
                filterLeft.setCoefficients(highPass);
                filterRight.setCoefficients(highPass);
                break;
            }
            default:
                return;
        }
    }

private:
    float lastCutoff = 0;
    SmoothedValue<float> cutoff;
    float q = 0;
    IIRFilter filter;
    IIRFilter filterLeft;
    IIRFilter filterRight;

    enum Filter {
        NO = 0,
        LOWPASS,
        HIGHPASS
    };
};
#endif //VENO_FILTERMODULE_H
