#pragma once

#include "../RawTable.h"

namespace VeNo {

    struct TriangleWave : public RawTable
    {
        static void startCreation();
        void generate () override;
    };
}