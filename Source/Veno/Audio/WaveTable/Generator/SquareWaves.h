#pragma once

#include "../RawTable.h"

namespace VeNo
{

    struct SquareWave : public RawTable
    {
        static void startCreation();
        void generate () override;
    };

    struct DirtySquareWave : public RawTable
    {
        static void startCreation();
        void generate () override;
    };
}