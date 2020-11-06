#include "LFOPage.h"

#include <utility>
#include "../../../../Utils.h"
#include "../../../../VenoInstance.h"

namespace VeNo
{

    LFOPage::LFOPage (std::string name, const std::string& pid)
            : GUICreator(pid), m_name(std::move(name)), m_helper(std::make_unique<GUIHelper>(m_processId, m_name))
    {
        m_helper->makeVisible(this);
    }

    void LFOPage::resized ()
    {
        m_helper->resizeComponents();
    }

    void LFOPage::paint (Graphics& g)
    {
        m_helper->drawBlocks(g);
    }

    LFOPage::~LFOPage ()
    {
        m_helper.reset(nullptr);
    }
}