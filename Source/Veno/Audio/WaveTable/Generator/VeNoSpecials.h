#pragma once

#include "../RawTable.h"


namespace VeNo
{

    struct SynthOne : public RawTable
    {
        static void startCreation();
        void generate () override;
    };

    struct SynthTwo : public RawTable
    {
        static void startCreation();
        void generate () override;
    };

    struct VeNoX : public RawTable
    {
        static void startCreation();
        void generate () override;
    };
}