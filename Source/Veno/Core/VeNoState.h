#ifndef VENO_VENOSTATE_H
#define VENO_VENOSTATE_H

#include <string>
#include "../GUI/GUIParts/Screens/ConfigScreen/VenoConfigScreen.h"
#include "../GUI/GUIParts/Screens/Debug/VeNoDebugScreen.h"
#include "../GUI/GUIParts/Screens/MatrixScreen/GuiMatrixScreen.h"
#include "../Services/ComponentStates.h"

class VeNoState
{
protected:
    std::string m_pid;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (VeNoState);
public:
    VeNoState (const std::string& pid);

    ~VeNoState ();

    VenoConfigScreen* configScreen = nullptr;
    VeNoDebugScreen* debugScreen = nullptr;
    VeNo::GuiMatrixScreen* matrix = nullptr;
    VeNo::ComponentStates componentStates;
    bool m_isFirstEditor = true;
    int m_lcd_mode = 0;
};

#endif //VENO_VENOSTATE_H
