#pragma once

#include "JuceHeader.h"
#include "../../BaseComponent.h"
#include "../../../../Core/VeNoListener.h"

#define RANDOM_TEXT_COUNT 6

namespace VeNo
{
    class LCDParameters : public BaseComponent,
                          public VeNoListener,
                          private Timer
    {
    public:
        LCDParameters (std::string& pid);

        ~LCDParameters () override;

        void parameterChanged (VeNoParameter* parameter) override;

        void notify (const std::string& name, double value) override;

        void resized () override;

        void paint (Graphics& g) override;

        void setIsStarting();

        bool m_isChangingData = false;
        bool m_isStarting = false;
    private:

        void timerCallback () override;
    protected:

        std::string m_changedParameter;
        double m_changedValue = 0;
        int m_ticks = 0;
        int m_time_needed = 30;
        std::string m_warmUpText[RANDOM_TEXT_COUNT] = {"Warmup...", "Mayonnaise", "Dont shake the baby",
                                                       "Awesome stuff",
                                                       "drink beer", "VeNo N3x"};
        int m_randomText = 0;
    };
}