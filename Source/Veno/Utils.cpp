#include "Utils.h"
#include "Core/Config.h"

float VeNo::Utils::DB_GAIN_CONVERSION_MULTIPLIER = 20.0f;
int VeNo::Utils::NOTES_PER_OCTAVE = 12;
int VeNo::Utils::CENTS_PER_NOTE = 100;
int VeNo::Utils::CENTS_PER_OCTAVE = NOTES_PER_OCTAVE * CENTS_PER_NOTE;
double VeNo::Utils::DOUBLE_PI = 6.283185307179586476925286766559;
double VeNo::Utils::PI = 3.14159265358979323846;

int VeNo::Utils::nextPowerOfTwo (float value)
{
    auto v = (unsigned int) value;
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
    double scale = Config::getInstance ()->getScale ();
    auto s = (float) (size * scale);
    g.setFont (s);
    return s;
}

float VeNo::Utils::clamp (float value, float min, float max)
{
    return value > max ? max : value < min ? min : value;
}

void VeNo::Utils::setPosition (int width, int height, int x, int y, BaseComponent& component, bool useMarginY)
{
    double scale = Config::getInstance ()->getScale ();
    int w = (int) (width * scale);
    int h = (int) (height * scale);
    if (useMarginY)
    {
        y += 10;
    }
    component.setBounds (x + 10, y, w, h);
}

void VeNo::Utils::setPositionSameRow (int width, int height, BaseComponent& component,
                                      BaseComponent& previous)
{
    setPosition (width, height, previous.getX () + previous.getWidth (), previous.getY (), component, false);
}

void VeNo::Utils::setPositionByPreviousRow (int width, int height, int x, BaseComponent& component,
                                            BaseComponent& previous)
{
    setPosition (width, height, x, previous.getY () + previous.getHeight (), component, false);
}

std::vector<int> VeNo::Utils::calcPosition (int width, int height, int prevWidth, int prevHeight)
{
    double scale = Config::getInstance ()->getScale ();
    int margin = getCalculatedHeight (10);
    int w = (int) (width * scale);
    int h = (int) (height * scale);
    int x = prevWidth + margin;
    int y = prevHeight + margin;
    return {x, y, w, h};
}

int VeNo::Utils::getCalculatedWidth (int width)
{
    return (int) (width * Config::getInstance ()->getScale ());
}

int VeNo::Utils::getCalculatedHeight (int height)
{
    return (int) (height * Config::getInstance ()->getScale ());
}

float VeNo::Utils::polyBlep (float t, float phaseInc)
{
    double dt = phaseInc / DOUBLE_PI;
    if (t < dt)
    {
        t /= (float) dt;
        return t + t - t * t - 1.0f;
    }
    else if (t > 1.0 - dt)
    {
        t = (t - 1.0f) / (float) dt;
        return t * t + t + t + 1.0f;
    }
    else return 0.0f;
}

float VeNo::Utils::lerp (float a, float b, float f)
{
    return (a + (b - a) * f);
}

float VeNo::Utils::centsToRatio (float cents)
{
    return std::pow (2.0, cents / (float) CENTS_PER_OCTAVE);
}

float VeNo::Utils::gainToDb (float gain)
{
    return DB_GAIN_CONVERSION_MULTIPLIER * std::log10 (gain);
}

float VeNo::Utils::dbToGain (float decibels)
{
    return std::pow (10.0, decibels / DB_GAIN_CONVERSION_MULTIPLIER);
}

float VeNo::Utils::dBForChannel (float value)
{
    return jmap (value, -30.0f, 0.0f, -1.0f,
                 0.9f);
}

float VeNo::Utils::getHigherValue (float a, float b)
{
    return a > b ? a : b;
}

float VeNo::Utils::waveTableMix (float a, float b, float mix)
{
    float diff = 1 - mix;
    a *= diff;
    b *= mix;
    return VeNo::Utils::clamp (a + b, -1, 1);
}
