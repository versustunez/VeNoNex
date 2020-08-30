#ifndef VENO_SIDERBARMIXERITEM_H
#define VENO_SIDERBARMIXERITEM_H

#include <string>
#include "JuceHeader.h"
#include "../../Components/BaseComponent.h"
#include "../../Components/Base/VeNoKnob.h"
#include "../../Components/Base/VeNoCheck.h"

class SidebarMixerItem : public BaseComponent
{
public:
    explicit SidebarMixerItem (const std::string& pid, int index);

    ~SidebarMixerItem () override;

private:
public:
    void resized () override;

    void paint (Graphics& g) override;

protected:
    int m_index;
    std::string m_name;
    std::string m_text;
    std::unique_ptr<VeNoCheck> m_onOffSwitch;
    std::unique_ptr<VeNoKnob> m_levelKnob;
};


#endif //VENO_SIDERBARMIXERITEM_H
