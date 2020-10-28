#include "WaveForms.h"
#include "../../../../Core/Config.h"
#include "../../../../VenoInstance.h"
#include "../../../../Utils.h"
#include "../../../Fonts/Fonts.h"

namespace VeNo
{
    WaveFormsGui::WaveFormsGui (std::string& pid)
            : BaseComponent (pid)
    {
        setMouseCursor (MouseCursor::PointingHandCursor);
        setInterceptsMouseClicks (true, false);
        m_fft = std::make_unique<FFT> ();
    }

    WaveFormsGui::~WaveFormsGui ()
    {
        m_fft.reset (nullptr);
    }

    void WaveFormsGui::resized ()
    {
    }

    void WaveFormsGui::paint (Graphics& g)
    {
        // mode -1 mean draw nothing! ;)
        if (mode > -1)
        {
            g.resetToDefaultState ();
            auto theme = Config::getInstance ()->getCurrentTheme ();
            if (theme == nullptr)
                return;

            g.setColour (theme->getColour (ThemeColour::lcd));
            if (mode == 0)
            {
                auto instance = VenoInstance::getInstance (BaseComponent::m_processId);
                g.setFont (*VenoFonts::getLCD ());
                int size = (int) VeNo::Utils::setFontSize (7, g);
                int halfWidth = getWidth () / 2;
                int halfHalfWidth = halfWidth / 2;
                g.drawText (std::to_string (instance->audioBuffer->leftPeak), halfWidth - halfHalfWidth - (size * 1.5),
                            size,
                            (size * 3), size, Justification::centred, false);
                g.drawText (std::to_string (instance->audioBuffer->rightPeak), halfWidth + halfHalfWidth - (size * 1.5),
                            size,
                            (size * 3), size, Justification::centred, false);
            }

            if (fill)
            {
                g.fillPath (m_path);
            }
            else
            {
                g.strokePath (m_path, juce::PathStrokeType (0.5f));
            }
        }
    }

    void WaveFormsGui::updatePaths (double val)
    {
        m_previous_value = val;
        switch (mode)
        {
            case 1:
                drawAudioOutput ();
                break;
            case 2:
                drawSpectrum ();
                break;
            case 3:
                drawWaveTable ();
                break;
            case 4:
                break;
            default:
                drawPeakMeter ();
        }
    }

    void WaveFormsGui::drawAudioOutput ()
    {
        fill = false;
        auto instance = VenoInstance::getInstance (BaseComponent::m_processId);
        auto buffer = instance->audioBuffer->getBuffer ();
        float posX = 0;
        float lastY = getHeight () / 2;
        float inc = (float) getWidth () / buffer.size ();
        m_path.clear ();
        for (float j : buffer)
        {
            auto height = ((j + 1) / 2) * getHeight ();
            m_path.addLineSegment ({posX, lastY, posX + inc, height}, 0.5f);
            posX += inc;
            lastY = height;
        }
    }

    void WaveFormsGui::drawSpectrum ()
    {
        m_fft->drawNextFrameOfSpectrum (VenoInstance::getInstance (m_processId)->audioBuffer->getBuffer ());
        fill = true;
        auto buffer = m_fft->scopeData;
        int size = m_fft->scopeSize;
        float posX = 0;
        float inc = (float) getWidth () / size;
        m_path.clear ();
        m_path.startNewSubPath (posX, getHeight ());
        for (int i = 0; i < size; i++)
        {
            float height = buffer[i] * getHeight ();
            posX += inc;
            m_path.lineTo (posX, height);
        }
        m_path.lineTo (posX, getHeight ());
        m_path.lineTo (0, getHeight ());
    }

    void WaveFormsGui::drawWaveTable ()
    {
        fill = false;
        m_path.clear ();
        auto inst = VenoInstance::getInstance (m_processId);
        auto hand = inst->handler;
        std::string osc = "osc" + std::to_string(inst->state->currentOscillator);
        auto& gen = WaveTableGenerator::getInstance ();
        auto base = gen.getGroup (hand->getParameter (osc + "__waveform_base")->getAsInt () - 1);
        auto sec = gen.getGroup (hand->getParameter (osc + "__waveform_sec")->getAsInt () - 1);
        auto mix = hand->getParameter (osc + "__waveform_mix")->getValue ();
        if (base == nullptr || sec == nullptr)
            return;

        auto realBaseWave = base->m_WaveTables[0];
        auto realSecWave = base->m_WaveTables[1];
        int size = realBaseWave->m_waveTableLen > realSecWave->m_waveTableLen ? realSecWave->m_waveTableLen
                                                                              : realBaseWave->m_waveTableLen;
        float inc = getWidth () / size;
        float x = 0;
        float lastY = -1;
        for (int i = 0; i < size; ++i)
        {
            auto y = VeNo::Utils::waveTableMix (realBaseWave->m_waveTable[0], realSecWave->m_waveTable[0], mix);
            float height = ((((y + 1) / 2) * -1) + 1) * getHeight ();
            if (lastY == -1)
            {
                lastY = height;
            }
            m_path.addLineSegment ({x, lastY, x + inc, height}, 0.5f);
            lastY = height;
            x += inc;
        }
    }

    void WaveFormsGui::drawPeakMeter ()
    {
        fill = true;
        auto instance = VenoInstance::getInstance (BaseComponent::m_processId);
        auto leftChannel = (float) VeNo::Utils::dBForChannel (instance->audioBuffer->leftPeak);
        auto rightChannel = (float) VeNo::Utils::dBForChannel (instance->audioBuffer->rightPeak);
        m_path.clear ();
        // leftChannel!
        float xLeft1 = 0.05 * getWidth (); // from pos -1,1 -0.9
        float xLeft2 = 0.46 * getWidth (); // from pos -1,1 -0.08
        m_path.addTriangle (
                xLeft1, leftChannel * getHeight (),
                xLeft1, getHeight (),
                xLeft2, getHeight ()
        );
        // leftChannel!
        xLeft1 = 0.95 * getWidth (); // from pos -1,1 0.9
        xLeft2 = 0.54 * getWidth (); // from pos -1,1 0.08
        m_path.addTriangle (
                xLeft1, rightChannel * getHeight (),
                xLeft1, getHeight (),
                xLeft2, getHeight ()
        );
    }
}