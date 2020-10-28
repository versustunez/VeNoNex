#pragma once

#include "WaveTableGenerator.h"

namespace VeNo
{
    struct RawTable
    {
        WaveForms m_index;
        WaveTableGroup* m_group = new WaveTableGroup();
        std::vector<double> m_freqWaveRe;
        std::vector<double> m_freqWaveIm;
        std::vector<double> m_tempRe;
        std::vector<double> m_tempIm;
        int m_len = 0;
        bool m_isRaw = false; // needed for Sine, Cosine...

        ~RawTable() = default;
        virtual void generate() = 0;
        void setSize(size_t size);
        void cleanUp();
        void cleanUpTemp();
        void finish() const;
    };
}