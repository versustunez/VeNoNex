#include "OscillatorPage.h"

#include <utility>
#include "../../../../Utils.h"
#include "../../../../VenoInstance.h"

namespace VeNo
{
    OscillatorPage::OscillatorPage (std::string name, const std::string& pid)
            : GUICreator (pid), m_name (std::move (name)), m_helper (std::make_unique<GUIHelper> (m_processId, m_name))
    {
        m_helper->makeVisible (this);
    }

    void OscillatorPage::resized ()
    {
        m_helper->resizeComponents ();
    }

    void OscillatorPage::paint (Graphics& g)
    {
        m_helper->drawBlocks (g);
    }

    OscillatorPage::~OscillatorPage ()
    {
        m_helper.reset(nullptr);
    }
}