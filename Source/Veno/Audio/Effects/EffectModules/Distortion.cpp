#include "Distortion.h"
#include "../../../VenoInstance.h"
#include "../../../Core/AudioConfig.h"

namespace VeNo
{
    Distortion::Distortion (std::string pid) : Effect (std::move (pid))
    {
        auto instance = VenoInstance::getInstance (pid)->handler;
        std::string d = "dist__";
        m_inputGain = instance->getParameter (d + "inGain");
        m_outputGain = instance->getParameter (d + "outGain");
        m_preLPValue = instance->getParameter (d + "preLP");
        m_preHPValue = instance->getParameter (d + "preHP");
        m_postLPValue = instance->getParameter (d + "postLP");
        m_postHPValue = instance->getParameter (d + "postHP");
        m_drive = instance->getParameter (d + "drive");
        m_type = instance->getParameter (d + "type");
        m_dynamic = instance->getParameter (d + "param1");
        m_mix = instance->getParameter (d + "mix");
    }

    void Distortion::prepare ()
    {
        auto sRate = AudioConfig::getInstance ()->m_sampleRate;
        m_preLP.update (m_preLPValue->getValue (), 1.0, sRate, FilterType::LP, 1.0);
        m_preHP.update (m_preHPValue->getValue (), 1.0, sRate, FilterType::HP, 1.0);
        m_postLP.update (m_postLPValue->getValue (), 1.0, sRate, FilterType::LP, 1.0);
        m_postHP.update (m_postLPValue->getValue (), 1.0, sRate, FilterType::HP, 1.0);
    }

    void Distortion::process (AudioBuffer<float>& audioBuffer)
    {

    }
}