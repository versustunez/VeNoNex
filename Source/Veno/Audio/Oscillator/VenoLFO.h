//
// Created by Maurice on 18.02.2020.
//

#ifndef VENO_VENOLFO_H
#define VENO_VENOLFO_H


#include "TableOscillators/VenoWaveTableOscillator.h"

class VenoLFO {
private:
    //max amount is 5
    float amount = 1;
    float rate = 0; //frequency
    VenoWaveTableOscillator tableHelper;
public:
    VenoLFO();
    ~VenoLFO();
    void setRate(float rate);
    void setAmount(float amount);
    void update();
    float getAmount(float amountStrength);
    float getRaw();
};


#endif //VENO_VENOLFO_H
