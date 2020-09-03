#pragma once

#include "../RawTable.h"

namespace VeNo
{
    struct SawWave : public RawTable
    {
        static void startCreation();
        void generate () override;
    };

    struct DirtySawWave : public RawTable
    {
        static void startCreation();
        void generate () override;
    };
}