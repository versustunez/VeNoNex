//
// Created by versustune on 17.03.20.
//

#ifndef VENO_CRAZYLOOK_H
#define VENO_CRAZYLOOK_H

#include "JuceHeader.h"

class CrazyLook : public LookAndFeel_V4
{
private:
public:
    CrazyLook() = default;
    ~CrazyLook() override = default;
protected:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CrazyLook)
};
#endif //VENO_CRAZYLOOK_H
