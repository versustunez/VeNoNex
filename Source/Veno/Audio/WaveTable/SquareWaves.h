//
// Created by versustune on 08.06.20.
//

#ifndef VENO_SQUAREWAVES_H
#define VENO_SQUAREWAVES_H

#include "WaveTableGenerator.h"

class SquareWaves
{
public:
    static void generateSquare(WaveTableGroup* group);
    static void generateDirtySquare(WaveTableGroup* group);
};
#endif //VENO_SQUAREWAVES_H
