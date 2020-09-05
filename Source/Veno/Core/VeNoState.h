#ifndef VENO_VENOSTATE_H
#define VENO_VENOSTATE_H

#include <string>
#include "../GUI/GUIParts/ConfigScreen/VenoConfigScreen.h"
#include "../GUI/GUIParts/Debug/VeNoDebugScreen.h"

class VeNoState
{
protected:
    std::string m_pid;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (VeNoState);
public:
    VeNoState (std::string pid);

    ~VeNoState ();

    VenoConfigScreen* configScreen = nullptr;
    VeNoDebugScreen* debugScreen = nullptr;
    bool m_isFirstEditor = true;
    int m_lcd_mode = 0;
};

#endif //VENO_VENOSTATE_H
