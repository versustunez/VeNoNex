// This File is Auto-Generated by the json-to-gui.js!

#include "EnvelopeGuiPart.h"

namespace VeNo
{
    void EnvelopeGuiPart::setupGui ()
    {
        // init background blocks 

        // init gui items --> make calls to createItem({});
        m_helper->createItem({"envelopewave", m_name,"Envelope-Wave",40,30,300,90, VeNoSelect::Type::NoSelect});
        m_helper->createItem({"slider", m_name + "__attack","Attack",380,35,70,85, VeNoSelect::Type::NoSelect});
        m_helper->createItem({"slider", m_name + "__decay","Decay",480,35,70,85, VeNoSelect::Type::NoSelect});
        m_helper->createItem({"slider", m_name + "__sustain","Sustain",580,35,70,85, VeNoSelect::Type::NoSelect});
        m_helper->createItem({"slider", m_name + "__release","Release",680,35,70,85, VeNoSelect::Type::NoSelect});
    }
}