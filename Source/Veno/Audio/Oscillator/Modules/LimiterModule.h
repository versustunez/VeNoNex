//
// Created by Maurice on 09.10.2019.
//

#ifndef VENO_LIMITERMODULE_H
#define VENO_LIMITERMODULE_H

#include "../../../Utils.h"
/*
this is a hard clipping limit! if values are greater then 1 stop it
*/
class VenoLimiterModule {
public:
    void apply(float *values) {
        values[0] = limit(values[0]);
        values[1] = limit(values[1]);
        values[2] = limit(values[2]);
    }

    float limit(float value) {
        return VeNo::Utils::clamp(value, -1, 1);
    }
};

#endif //VENO_LIMITERMODULE_H
