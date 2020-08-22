#ifndef VENO_VIBRATO_H
#define VENO_VIBRATO_H

#include "../VenoLFO.h"

class VenoVibratoModule {
public:
    ~VenoVibratoModule() = default;

    void update() {
        lfo->update();
    }

    float apply(float amountStrength) {
        if (!isActive || lfo == nullptr) {
            return 0.0;
        }
        return lfo->getAmount(amountStrength);
    }

    VenoLFO *lfo;
    bool isActive = false;
};

#endif //VENO_VIBRATO_H
