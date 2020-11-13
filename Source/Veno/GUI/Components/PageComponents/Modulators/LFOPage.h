#pragma once

#include "../../BaseComponent.h"
#include "../../Base/VeNoSelect.h"
#include "../../../../Services/GUIHelper.h"
#include "../../../../Services/GUICreator.h"

namespace VeNo
{

    /**
     * Class that Holds everything a Oscillator can use! It's not for the LFO
     * Waveform, Unison, Envelope, Pitch, OSC-Main (Phase, Random-Phase, Pan), Limiter
     */
    class LFOPage : public GUICreator
    {
    public:
        LFOPage (std::string  name, const std::string& pid);

        ~LFOPage () override;

        void resized () override;

        void paint (Graphics& g) override;

        // method is generated by json-to-gui.js!
        void setupGui () override;

    protected:
        std::string m_name;
        std::unique_ptr<GUIHelper> m_helper;
    };
}