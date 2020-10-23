#include "GuiMatrixComponent.h"

namespace VeNo
{
    GuiMatrixComponent::GuiMatrixComponent (std::string& pid)
            : m_pid (pid), m_footer (std::make_unique<GuiMatrixFooter> (m_pid)),
              m_list (std::make_unique<GuiMatrixList> (m_pid))
    {
        addAndMakeVisible (*m_footer);
        setViewedComponent (m_list.get (), false);
    }

    GuiMatrixComponent::~GuiMatrixComponent ()
    {
        m_footer.reset (nullptr);
        m_list.reset (nullptr);
    }

    void GuiMatrixComponent::resized ()
    {
        m_list->setBounds (0, 0, getWidth (), getHeight () - 100);
        m_footer->setBounds (0, getHeight () - 100, getWidth (), 100);
    }

    void GuiMatrixComponent::paint (Graphics& g)
    {

    }
}