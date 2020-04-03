//
// Created by versustune on 17.03.20.
//

#include "LookHandler.h"
#include "../../Core/Config.h"

LookHandler::LookHandler() {
    selectLook(Config::getInstance()->getCurrentLook());
}

LookHandler::~LookHandler() {
    //delete this shit!
    delete feels[0];
    delete feels[1];
}

void LookHandler::selectLook(int index) {
    currentLook = index;
}
