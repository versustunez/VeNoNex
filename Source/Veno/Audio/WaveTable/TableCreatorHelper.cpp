#include "TableCreatorHelper.h"
#include "../../Core/AudioConfig.h"
#include "../../Utils.h"

namespace VeNo
{
    void TableCreatorHelper::createTable (RawTable& table)
    {
        table.setSize (findTableLen ());
        table.generate ();
        if (table.m_isRaw)
        {
            createTableRaw (table);
            return;
        }
        fillTables (table);
        table.finish ();
    }

    void TableCreatorHelper::createTableRaw (RawTable& table)
    {
        auto group = table.m_group;
        auto topFreq = AudioConfig::getInstance ()->getSampleRate () / 2;
        auto index = group->m_numWaveTables;
        createWaveTableOnIndex (table, index, topFreq);
        auto& waveTable = group->m_WaveTables[index]->m_waveTable;
        for (long x = 0; x < table.m_len; x++)
            waveTable[x] = table.m_freqWaveRe[x];
        waveTable[table.m_len] = waveTable[0];
        table.finish ();
    }

    double TableCreatorHelper::makeWaveTable (RawTable& table, double scale, double topFreq)
    {
        fft (table.m_len, table);
        auto& ai = table.m_tempIm;
        auto& ar = table.m_tempRe;
        auto len = table.m_len;
        auto group = table.m_group;
        scale = getScale (table, scale);

        if (group->m_numWaveTables > WaveTableGroup::numWaveTableSlots)
            return 0;

        auto index = group->m_numWaveTables;
        createWaveTableOnIndex (table, index, topFreq);
        auto& waveTable = group->m_WaveTables[index]->m_waveTable;
        for (long idx = 0; idx < len; idx++)
            waveTable[idx] = ai[idx] * scale;

        waveTable[len] = waveTable[0];

        return 0.0;
    }

    int TableCreatorHelper::findTableLen ()
    {
        int maxHarms = std::lround (AudioConfig::getInstance ()->getSampleRate () / (3.0 * 20));
        return Utils::nextPowerOfTwo (maxHarms);
    }

    double TableCreatorHelper::getNextRand ()
    {
        return ((std::rand () / double (RAND_MAX)) * 2) - 1;
    }

    int TableCreatorHelper::fillTables (RawTable& table)
    {
        auto& freqWaveRe = table.m_freqWaveRe;
        auto& freqWaveIm = table.m_freqWaveIm;
        auto& ar = table.m_tempRe;
        auto& ai = table.m_tempIm;

        freqWaveRe[0] = freqWaveIm[0] = 0.0;
        freqWaveRe[table.m_len >> 1] = freqWaveIm[table.m_len >> 1] = 0.0;

        unsigned int maxHarmonic = table.m_len >> 1u;
        const double minValue = 0.000001;
        while ((std::fabs (freqWaveRe[maxHarmonic]) + std::fabs (freqWaveIm[maxHarmonic]) < minValue) &&
               maxHarmonic)
            --maxHarmonic;
        double topFreq = 2.0 / 3.0 / maxHarmonic;
        double scale = 0.0;
        int numTables = 0;
        while (maxHarmonic)
        {
            table.cleanUpTemp ();
            int i;
            int numSamples = table.m_len;
            for (i = 1; i <= maxHarmonic; i++)
            {
                ar[i] = freqWaveRe[i];
                ai[i] = freqWaveIm[i];
                ar[numSamples - i] = freqWaveRe[numSamples - i];
                ai[numSamples - i] = freqWaveIm[numSamples - i];
            }
            scale = makeWaveTable (table, scale, topFreq);
            numTables++;
            topFreq *= 2;
            maxHarmonic >>= 1u;
        }
        return numTables;
    }


    void TableCreatorHelper::fft (unsigned int N, RawTable& table)
    {
        auto& ar = table.m_tempRe;
        auto& ai = table.m_tempIm;
        int i, j, k, L;            /* indexes */
        int M, TEMP, LE, LE1, ip;  /* M = log N */
        int NV2, NM1;
        double t;               /* temp */
        double Ur, Ui, Wr, Wi, Tr, Ti;
        double Ur_old;

        // if ((N > 1) && !(N & (N - 1)))   // make sure we have a power of 2

        NV2 = N >> 1;
        NM1 = N - 1;
        TEMP = N; /* get M = log N */
        M = 0;
        while (TEMP >>= 1) ++M;

        /* shuffle */
        j = 1;
        for (i = 1; i <= NM1; i++)
        {
            if (i < j)
            {             /* swap a[i] and a[j] */
                t = ar[j - 1];
                ar[j - 1] = ar[i - 1];
                ar[i - 1] = t;
                t = ai[j - 1];
                ai[j - 1] = ai[i - 1];
                ai[i - 1] = t;
            }

            k = NV2;             /* bit-reversed counter */
            while (k < j)
            {
                j -= k;
                k /= 2;
            }

            j += k;
        }

        LE = 1.;
        for (L = 1; L <= M; L++)
        {            // stage L
            LE1 = LE;                         // (LE1 = LE/2)
            LE *= 2;                          // (LE = 2^L)
            Ur = 1.0;
            Ui = 0.;
            Wr = std::cos (Utils::PI / (float) LE1);
            Wi = -std::sin (Utils::PI / (float) LE1); // Cooley, Lewis, and Welch have "+" here
            for (j = 1; j <= LE1; j++)
            {
                for (i = j; i <= N; i += LE)
                { // butterfly
                    ip = i + LE1;
                    Tr = ar[ip - 1] * Ur - ai[ip - 1] * Ui;
                    Ti = ar[ip - 1] * Ui + ai[ip - 1] * Ur;
                    ar[ip - 1] = ar[i - 1] - Tr;
                    ai[ip - 1] = ai[i - 1] - Ti;
                    ar[i - 1] = ar[i - 1] + Tr;
                    ai[i - 1] = ai[i - 1] + Ti;
                }
                Ur_old = Ur;
                Ur = Ur_old * Wr - Ui * Wi;
                Ui = Ur_old * Wi + Ui * Wr;
            }
        }
    }

    double TableCreatorHelper::getScale (RawTable& table, double scale)
    {
        if (scale == 0.0)
        {
            auto& ai = table.m_tempIm;
            auto len = table.m_len;
            double max = 0;
            for (int idx = 0; idx < len; idx++)
            {
                double temp = std::fabs (ai[idx]);
                if (max < temp)
                    max = temp;
            }
            return 1.0 / max * .999;
        }
        return 0.0;
    }

    void TableCreatorHelper::createWaveTableOnIndex (RawTable& table, int index, double topFreq)
    {
        auto group = table.m_group;
        auto len = table.m_len;
        auto tableObj = group->m_WaveTables[index] = new WaveTableObject ();
        auto& waveTable = group->m_WaveTables[index]->m_waveTable;
        waveTable.resize (len + 1);
        tableObj->m_waveTableLen = len;
        tableObj->m_topFreq = topFreq;
        ++group->m_numWaveTables;
    }
}