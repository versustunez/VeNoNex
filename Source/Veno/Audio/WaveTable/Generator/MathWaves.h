#pragma once

#include "../RawTable.h"

namespace VeNo
{
    struct SineWave : public RawTable
    {
        static void startCreation();
        void generate () override;
    };

    struct CosineWave : public RawTable
    {
        static void startCreation();
        void generate () override;
    };
}