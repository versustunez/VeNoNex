//
// Created by versustune on 17.03.20.
//

#ifndef VENO_BASECOMPONENT_H
#define VENO_BASECOMPONENT_H

#include "JuceHeader.h"
#include <string>

/**
 * this is the base Component of all VeNo Components... it has all important Methods
 */
class BaseComponent : public Component {
private:
    std::string prefix;
public:
    BaseComponent() = default;
    ~BaseComponent() = default;

protected:
};


#endif //VENO_BASECOMPONENT_H
