#pragma once
#include <string>
#include "JuceHeader.h"

namespace VeNo
{
    class Effect
    {
    public:
        explicit Effect (std::string pid);

        virtual ~Effect () = default;

        virtual void prepare () = 0;

        virtual void process (juce::AudioBuffer<float>& audioBuffer) = 0;

        bool isActive = false;
    protected:
        std::string m_processId;
    };
}