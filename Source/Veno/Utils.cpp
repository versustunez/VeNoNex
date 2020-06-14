//
// Created by versustune on 08.06.20.
//

#include "Utils.h"
#include "Core/Config.h"

int VeNo::Utils::nextPowerOfTwo (float value)
{
    unsigned int v = value;
    v--;
    v |= v >> 1;
    v |= v >> 2;
    v |= v >> 4;
    v |= v >> 8;
    v |= v >> 16;
    v++;
    return v;
}

float VeNo::Utils::setFontSize (float size, Graphics& g)
{
    double scale = Config::getInstance()->getScale();
    float s = size * scale;
    g.setFont(s);
    return s;
}

float VeNo::Utils::clamp (float value, float min, float max)
{
    return value > max ? max : value < min ? min : value;
}

void
VeNo::Utils::setPosition (int width, int height, int x, int y, std::shared_ptr<Component> component, bool useMarginY)
{
    double scale = Config::getInstance()->getScale();
    double w = width * scale;
    double h = height * scale;
    if (useMarginY)
    {
        y += 10;
    }
    component->setBounds(x + 10, y, w, h);
}

void VeNo::Utils::setPositionSameRow (int width, int height, std::shared_ptr<Component> component,
                                      std::shared_ptr<Component> previous)
{
    setPosition(width, height, previous->getX() + previous->getWidth(), previous->getY(), component, false);
}

void VeNo::Utils::setPositionByPreviousRow (int width, int height, int x, std::shared_ptr<Component> component,
                                            std::shared_ptr<Component> previous)
{
    setPosition(width, height, x, previous->getY() + previous->getHeight(), component, true);
}

std::vector<int> VeNo::Utils::calcPosition (int width, int height, int prevWidth, int prevHeight)
{
    double scale = Config::getInstance()->getScale();
    int w = (width * scale);
    int h = (height * scale);
    int x = prevWidth + 10;
    int y = prevHeight + 10;
    return {x, y, w, h};
}

int VeNo::Utils::getCalculatedWidth (int width)
{
    return width * Config::getInstance()->getScale();
}

int VeNo::Utils::getCalculatedHeight (int height)
{
    return height * Config::getInstance()->getScale();
}
