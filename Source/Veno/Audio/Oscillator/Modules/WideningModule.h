//
// Created by Maurice on 09.10.2019.
//

#ifndef VENO_WIDEMODULE_H
#define VENO_WIDEMODULE_H

class VenoWidenessModule {
public:
    void setCoeff(float wide) {
        float _width = wide / 200;
        float tmp = 1 / fmax(1 + _width, 2);
        coeffM = 1 * tmp;
        coeff = _width * tmp;
        detuneCoeff = coeff * .3;
    }

    void apply(float *input) {
        float mid = (input[1] + input[2]) * coeffM;
        float stereo = (input[2] - input[1]) * coeff;
        input[1] = mid - stereo;
        input[2] = mid + stereo;
    }

    float getDetuneWideness() {
        return detuneCoeff;
    }

private:
    double coeff = 0;
    double coeffM = 0;
    double detuneCoeff = 0;
};

#endif //VENO_WIDEMODULE_H
