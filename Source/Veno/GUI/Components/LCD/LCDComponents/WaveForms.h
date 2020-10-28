#pragma once

#include "JuceHeader.h"
#include "../../BaseComponent.h"
#include "../../../../Services/FFT.h"

namespace VeNo
{
    class WaveFormsGui : public BaseComponent
    {
    public:
        explicit WaveFormsGui (std::string& pid);

        ~WaveFormsGui () override;

        int mode = -1;
        bool fill = true;

        void paint (Graphics& g) override;

        void resized () override;

        void updatePaths (double val);

    protected:
        Path m_path;
        std::unique_ptr<FFT> m_fft;
        double m_previous_value = 0;

        void drawAudioOutput ();

        void drawSpectrum ();

        void drawWaveTable ();

        void drawPeakMeter ();
    };
}