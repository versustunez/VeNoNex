//
// Created by versustune on 17.03.20.
//

#include "LookHandler.h"
#include "../../Core/Config.h"

LookHandler::LookHandler ()
{
    selectLook(Config::getInstance()->getCurrentLook());
}

LookHandler::~LookHandler ()
{
    //delete this shit!
    delete m_feels[0];
    delete m_feels[1];
    m_look.reset();
}

void LookHandler::selectLook (int index)
{
    m_currentLook = index;
}

LookAndFeel_V4* LookHandler::getLook ()
{
    return m_feels[m_currentLook];
}
