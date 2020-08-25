#include "VenoLogo.h"

VenoLogo* VenoLogo::instance = nullptr;

VenoLogo* VenoLogo::getInstance ()
{
    if (instance == nullptr)
    {
        instance = new VenoLogo ();
    }
    return instance;
}

VenoLogo::VenoLogo ()
{
    MemoryOutputStream mo;
    auto result = ImageCache::getFromMemory (BinaryData::LogoVeNo_png, BinaryData::LogoVeNo_pngSize);
    realLogo = result;
}

Image VenoLogo::getLogo ()
{
    return getInstance ()->realLogo;
}

void VenoLogo::deleteInstance ()
{
    delete instance;
    instance = nullptr;
}
