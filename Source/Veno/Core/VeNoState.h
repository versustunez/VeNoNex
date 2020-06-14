//
// Created by versustune on 14.06.20.
//

#ifndef VENO_VENOSTATE_H
#define VENO_VENOSTATE_H

#include <string>
#include "../GUI/GUIParts/ConfigScreen/VenoConfigScreen.h"

class VeNoState
{
protected:
    std::string m_pid = "";
public:
    VeNoState(std::string pid);
    ~VeNoState();
    VenoConfigScreen* configScreen = nullptr;
};
#endif //VENO_VENOSTATE_H
