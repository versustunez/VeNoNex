//
// Created by versustune on 13.06.20.
//

#ifndef VENO_SIDEBARMIXER_H
#define VENO_SIDEBARMIXER_H

#include "JuceHeader.h"
#include "../../Components/BaseComponent.h"

class SidebarMixer : public BaseComponent
{
private:
public:
    SidebarMixer (const std::string& processId);
    ~SidebarMixer() = default;
protected:
};

#endif //VENO_SIDEBARMIXER_H
