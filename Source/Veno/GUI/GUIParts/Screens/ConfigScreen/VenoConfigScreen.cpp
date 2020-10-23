#include "VenoConfigScreen.h"
#include "../../../../VenoInstance.h"

VenoConfigScreen::VenoConfigScreen (const std::string& pid) : DocumentWindow ("VeNo Config", Colours::black,
                                                                              DocumentWindow::closeButton, true),
                                                              m_pid (pid),
                                                              component (std::make_shared<ConfigComponent> (m_pid))
{
    auto w = 840;
    auto h = 800;
    component->setSize (w, h);
    m_lookHandler = std::make_unique<LookHandler> ();
    component->setLookAndFeel (m_lookHandler.get());
    centreWithSize (w, h);
    setAlwaysOnTop (true);
    setContentOwned (component.get (), false);
    setResizable (false, false);
    setUsingNativeTitleBar (true);
    setVisible (true);
}

VenoConfigScreen::~VenoConfigScreen ()
{
    component->setLookAndFeel (nullptr);
    m_lookHandler.reset ();
    component.reset ();
}

void VenoConfigScreen::closeButtonPressed ()
{
    auto state = VenoInstance::getInstance (m_pid)->state;
    if (state != nullptr && state->configScreen != nullptr)
    {
        delete state->configScreen;
        state->configScreen = nullptr;
    }
}

void VenoConfigScreen::paint (Graphics& graphics)
{
}

void VenoConfigScreen::resized ()
{
}
