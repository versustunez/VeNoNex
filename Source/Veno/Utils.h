//
// Created by versustune on 08.06.20.
//

#ifndef VENO_UTILS_H
#define VENO_UTILS_H

#include "JuceHeader.h"

namespace VeNo {
    class Utils {
    public:
        Utils() = default;
        ~Utils() = default;
        static int nextPowerOfTwo(float value);

        static float setFontSize(float size, Graphics &g);
    };
}


#endif //VENO_UTILS_H
