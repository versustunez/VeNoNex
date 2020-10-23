#include "GuiMatrixScreen.h"
#include "../../../../VenoInstance.h"

namespace VeNo
{
    GuiMatrixScreen::GuiMatrixScreen (const std::string& pid) : DocumentWindow ("VeNo Matrix", Colours::black,
                                                                                DocumentWindow::closeButton, true),
                                                                m_pid (pid),
                                                                m_component (
                                                                        std::make_shared<GuiMatrixComponent> (m_pid))
    {
        auto w = 840;
        auto h = 800;
        m_component->setSize (w, h);
        m_lookHandler = std::make_unique<LookHandler> ();
        m_component->setLookAndFeel (m_lookHandler.get());
        centreWithSize (w, h);
        setAlwaysOnTop (true);
        setContentOwned (m_component.get (), false);
        setResizable (false, false);
        setUsingNativeTitleBar (true);
        setVisible (true);
    }

    GuiMatrixScreen::~GuiMatrixScreen ()
    {
        m_component->setLookAndFeel (nullptr);
        m_lookHandler.reset ();
        m_component.reset ();
    }

    void GuiMatrixScreen::closeButtonPressed ()
    {
        auto state = VenoInstance::getInstance (m_pid)->state;
        if (state != nullptr && state->matrix != nullptr)
        {
            delete state->matrix;
            state->matrix = nullptr;
        }
    }

    void GuiMatrixScreen::paint (Graphics& graphics)
    {
    }

    void GuiMatrixScreen::resized ()
    {
    }
}