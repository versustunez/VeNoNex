//
// Created by versustune on 08.06.20.
//

#include "Utils.h"
#include "Core/Config.h"

int VeNo::Utils::nextPowerOfTwo(float value) {
    unsigned int v = value;
    v--;
    v |= v >> 1;
    v |= v >> 2;
    v |= v >> 4;
    v |= v >> 8;
    v |= v >> 16;
    v++;
    return v;
}

float VeNo::Utils::setFontSize(float size, Graphics &g) {
    double scale = Config::getInstance()->getScale();
    float s = size * scale;
    g.setFont(s);
    return s;
}