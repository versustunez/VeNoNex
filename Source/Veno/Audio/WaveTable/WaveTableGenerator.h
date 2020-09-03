#pragma once

#include "JuceHeader.h"
#include "WaveTableStructs.h"

namespace VeNo
{
    class WaveTableGenerator
    {
    private:
        static constexpr int numWaveTableSlots = 40;
        std::vector<WaveTableGroup*> m_waveTables{numWaveTableSlots};
    public:
        static WaveTableGenerator& getInstance ()
        {
            static WaveTableGenerator instance;
            return instance;
        }

        WaveTableGroup* getGroup (int id);

        void init ();

        void cleanTables ();

        void setGroup(WaveForms index, WaveTableGroup* group);

    protected:
        bool m_isInit = false;
        int addedWaveForms = 0;

        WaveTableGenerator () = default;

        ~WaveTableGenerator () = default;
        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (WaveTableGenerator)
    };
}
