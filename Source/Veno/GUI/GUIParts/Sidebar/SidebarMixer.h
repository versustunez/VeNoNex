#ifndef VENO_SIDEBARMIXER_H
#define VENO_SIDEBARMIXER_H

#include "JuceHeader.h"
#include "../../Components/BaseComponent.h"
#include "../../Components/Base/VeNoCheck.h"
#include "../../Components/Base/VeNoKnob.h"
#include "SiderbarMixerItem.h"

class SidebarMixer : public BaseComponent
{
private:
public:
    explicit SidebarMixer (const std::string& processId);

    void resized () override;

    void paint (Graphics& g) override;

protected:
    std::vector<std::unique_ptr<SidebarMixerItem>> m_mixerItems;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SidebarMixer)
};

#endif //VENO_SIDEBARMIXER_H
