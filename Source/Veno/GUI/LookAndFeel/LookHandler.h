//
// Created by versustune on 17.03.20.
//

#ifndef VENO_LOOKHANDLER_H
#define VENO_LOOKHANDLER_H

#include "JuceHeader.h"
#include "CrazyLook.h"
#include "FlatLook.h"
#include <memory>

/**
 * overwrite the basic look and feel based on the selected Look and Feel :)
 */
class LookHandler : public LookAndFeel_V4 {
private:
    std::shared_ptr<LookAndFeel_V4> look;
    int currentLook = 0;
public:
    LookHandler();
    ~LookHandler();
    void selectLook(int index);
protected:
    //currently both available themes are CrazyLook <-- (this is a fun one xD) and FlatLook
    LookAndFeel_V4 *feels[2] = {new FlatLook(), new CrazyLook()};
};


#endif //VENO_LOOKHANDLER_H
