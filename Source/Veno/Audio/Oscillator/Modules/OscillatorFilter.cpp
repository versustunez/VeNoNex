#include "OscillatorFilter.h"
#include "../../../VenoInstance.h"
#include "../../../Core/AudioConfig.h"
#include <utility>

VeNo::OscillatorFilter::OscillatorFilter (std::string id, const std::string& name)
        : m_pid (std::move (id)), m_name (name + "__")
{
    auto inst = VenoInstance::getInstance (m_pid)->handler;
    m_qFactor = inst->getParameter (m_name + "filter_q");
    m_cutOff = inst->getParameter (m_name + "filter_cutoff");
    m_type = inst->getParameter (m_name + "filter_type");
}

VeNo::OscillatorFilter::~OscillatorFilter ()
= default;

void VeNo::OscillatorFilter::update ()
{
    int selType = (int) m_type->getValueForVoice (m_voice);
    FilterType type;
    switch (selType)
    {
        case 2:
            type = FilterType::LP;
            break;
        case 3:
            type = FilterType::HP;
            break;
        case 4:
            type = FilterType::BP;
            break;
        case 5:
            type = FilterType::NOTCH;
            break;
        default:
            type = FilterType::NO;
    }
    m_filter.update (
            m_cutOff->getValueForVoice (m_voice),
            m_qFactor->getValueForVoice (m_voice),
            AudioConfig::getInstance ()->m_sampleRate,
            type,
            1.0
    );
}
