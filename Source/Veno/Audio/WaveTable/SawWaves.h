//
// Created by versustune on 08.06.20.
//

#ifndef VENO_SAWWAVES_H
#define VENO_SAWWAVES_H

#include "WaveTableGenerator.h"

class SawWaves
{
public:
    static void generateSaw(WaveTableGroup* group);
    static void generateDirtySaw(WaveTableGroup* group);
};

#endif //VENO_SAWWAVES_H
