#include "SidebarMixer.h"

#include "../../../Utils.h"

SidebarMixer::SidebarMixer (const std::string& processId) : BaseComponent (processId)
{
    m_mixerItems.resize (4);

    for (int i = 0; i < 4; ++i)
    {
        m_mixerItems[i] = std::make_unique<SidebarMixerItem> (processId, i);
        addAndMakeVisible (*m_mixerItems[i]);
    }
}

void SidebarMixer::resized ()
{
    auto width = getWidth () / 4;
    int x = 0;
    for (int i = 0; i < 4; ++i)
    {
        m_mixerItems[i]->setBounds (x, 0, width, getHeight ());
        x += width;
    }
}

void SidebarMixer::paint (Graphics& g)
{
    BaseComponent::paint (g);
}

