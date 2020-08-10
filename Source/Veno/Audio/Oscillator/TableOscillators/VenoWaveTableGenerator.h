//
// Created by versustune on 2020-02-28.
//

#ifndef VENO_VENOWAVETABLEGENERATOR_H
#define VENO_VENOWAVETABLEGENERATOR_H

struct WaveTableObject {
    double topFreq;
    int waveTableLen;
    float *waveTable;
};

struct WaveTableGroup {
    static constexpr int numWaveTableSlots = 40;
    WaveTableObject *mWaveTables[numWaveTableSlots] = {};
    int numWaveTables = 0;
};

class VenoWaveTableGenerator {
private:
    static constexpr int numWaveTableSlots = 40;
    WaveTableGroup *waveTables[numWaveTableSlots] = {};
public:
    float sampleRate = 44100.0f;
    enum WaveForms {
        SAW = 0,
        SINE,
        SQUARE,
        TRIANGLE,
        wSaw,
        wSQUARE, //that stuff is to dirty xD,
        SYNTHONE,
        SYNTHTWO,
        VENOX
    };

    static VenoWaveTableGenerator &getInstance() {
        static VenoWaveTableGenerator instance;
        return instance;
    }
    WaveTableGroup *getGroup(int id);
    void init();
protected:
    bool isInit = false;
    VenoWaveTableGenerator() = default;
    ~VenoWaveTableGenerator() = default;
};


#endif //VENO_VENOWAVETABLEGENERATOR_H
