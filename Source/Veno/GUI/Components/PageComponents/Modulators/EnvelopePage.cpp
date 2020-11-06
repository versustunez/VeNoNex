#include "EnvelopePage.h"
#include "../../../../Utils.h"

namespace VeNo
{
    EnvelopePage::EnvelopePage (std::string name, const std::string& pid)
            : BaseComponent (pid), m_name (std::move (name))
    {
        m_guiParts.push_back (std::make_unique<EnvelopeGuiPart> ("Envelope(Voices)", "env1", m_processId));
        m_guiParts.push_back (std::make_unique<EnvelopeGuiPart> ("Envelope(Free)", "env2", m_processId));
        addAndMakeVisible(*m_guiParts[0]);
        addAndMakeVisible(*m_guiParts[1]);
    }

    EnvelopePage::~EnvelopePage ()
    {
        m_guiParts.clear();
    }

    void EnvelopePage::resized ()
    {
        m_guiParts[0]->setBounds (
                Utils::getScaledSize (20),
                Utils::getScaledSize (70),
                Utils::getScaledSize (850),
                Utils::getScaledSize (150)
        );
        m_guiParts[1]->setBounds (
                Utils::getScaledSize (20),
                Utils::getScaledSize (300),
                Utils::getScaledSize (850),
                Utils::getScaledSize (150)
        );
    }

    void EnvelopePage::paint (Graphics& g)
    {
    }
}