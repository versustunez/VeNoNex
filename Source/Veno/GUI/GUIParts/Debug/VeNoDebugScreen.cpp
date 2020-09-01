#include "VeNoDebugScreen.h"
#include "../../../VenoInstance.h"

VeNoDebugScreen::VeNoDebugScreen (const std::string& pid) : DocumentWindow ("VeNo Debugger", Colours::black,
                                                                            DocumentWindow::allButtons, true)
{
    m_pid = pid;
    auto w = 1270;
    auto h = 800;
    component = std::make_shared<VeNoDebugComponent> (m_pid);
    component->setSize (w, h);
    m_lookHandler = std::make_unique<LookHandler> ();
    component->setLookAndFeel (m_lookHandler->getLook ());
    centreWithSize (w, h);
    setAlwaysOnTop (true);
    setContentOwned (component.get (), false);
    setResizable (true, true);
    setUsingNativeTitleBar (true);
    setVisible (true);
}

VeNoDebugScreen::~VeNoDebugScreen ()
{
    component->setLookAndFeel (nullptr);
    m_lookHandler.reset ();
    component.reset ();
}

void VeNoDebugScreen::closeButtonPressed ()
{
    auto state = VenoInstance::getInstance (m_pid)->state;
    if (state != nullptr && state->debugScreen != nullptr)
    {
        delete state->debugScreen;
        state->debugScreen = nullptr;
    }
}

void VeNoDebugScreen::paint (Graphics& graphics)
{
}

void VeNoDebugScreen::resized ()
{
    if (component != nullptr)
        component->setSize (getWidth (), getHeight ());
}
