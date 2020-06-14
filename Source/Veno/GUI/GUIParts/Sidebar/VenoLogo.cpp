//
// Created by versustune on 14.06.20.
//

#include "VenoLogo.h"

VenoLogo* VenoLogo::instance = nullptr;

VenoLogo* VenoLogo::getInstance ()
{
    if (instance == nullptr)
    {
        instance = new VenoLogo();
    }
    return instance;
}

VenoLogo::VenoLogo ()
{
    MemoryOutputStream mo;
    auto result = Base64::convertFromBase64(mo, base64logo);
    if (result)
    {
        realLogo = juce::PNGImageFormat::loadFrom(mo.getData(), mo.getDataSize());
    }
}

Image VenoLogo::getLogo ()
{
    return getInstance()->realLogo;
}

void VenoLogo::deleteInstance ()
{
    delete instance;
}
