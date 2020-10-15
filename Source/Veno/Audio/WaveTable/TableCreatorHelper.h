#pragma once

#include <cmath>
#include <cstdlib>
#include "WaveTableGenerator.h"
#include "RawTable.h"


namespace VeNo {
    struct TableCreatorHelper {
        static void fft (unsigned int N, RawTable& table);
        static double makeWaveTable(RawTable& table, double scale, double topFreq);
        static int findTableLen();
        static double getNextRand();
        static int fillTables(RawTable& table);
        static void createTable(RawTable& table);
        static void createTableRaw(RawTable& table);
        static double getScale(RawTable& table, double scale);
        static void createWaveTableOnIndex(RawTable& table, int index, double topFreq);
        static void findCutoff(double topFreq, RawTable& table);
    };
}
