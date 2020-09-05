#include "Utils.h"
#include "Core/Config.h"

double VeNo::Utils::DB_GAIN_CONVERSION_MULTIPLIER = 20.0;
int VeNo::Utils::NOTES_PER_OCTAVE = 12;
int VeNo::Utils::CENTS_PER_NOTE = 100;
int VeNo::Utils::CENTS_PER_OCTAVE = NOTES_PER_OCTAVE * CENTS_PER_NOTE;
double VeNo::Utils::DOUBLE_PI = 6.283185307179586476925286766559;
double VeNo::Utils::PI = 3.14159265358979323846;
double VeNo::Utils::HALF_PI = 1.57079632679489661923;

int VeNo::Utils::nextPowerOfTwo (double value)
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

double VeNo::Utils::setFontSize (double size, Graphics& g)
{
    double scale = Config::getInstance ()->getScale ();
    auto s = (double) (size * scale);
    g.setFont (s);
    return s;
}

double VeNo::Utils::clamp (double value, double min, double max)
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
    int margin = getScaledSize (10);
    int w = getScaledSize(width);
    int h = getScaledSize(height);
    int x = prevWidth + margin;
    int y = prevHeight + margin;
    return {x, y, w, h};
}

int VeNo::Utils::getScaledSize (int width)
{
    return static_cast<int>(width * Config::getInstance ()->getScale ());
}

double VeNo::Utils::polyBlep (double t, double phaseInc)
{
    double dt = phaseInc / DOUBLE_PI;
    if (t < dt)
    {
        t /= dt;
        return t + t - t * t - 1.0f;
    }
    else if (t > 1.0 - dt)
    {
        t = (t - 1.0f) / dt;
        return t * t + t + t + 1.0f;
    }
    else return 0.0f;
}

double VeNo::Utils::lerp (double a, double b, double f)
{
    return (a + (b - a) * f);
}

double VeNo::Utils::centsToRatio (double cents)
{
    return std::pow (2.0, cents / (double) CENTS_PER_OCTAVE);
}

double VeNo::Utils::gainToDb (double gain)
{
    return DB_GAIN_CONVERSION_MULTIPLIER * std::log10 (gain);
}

double VeNo::Utils::dbToGain (double decibels)
{
    return std::pow (10.0, decibels / DB_GAIN_CONVERSION_MULTIPLIER);
}

double VeNo::Utils::dBForChannel (double value)
{
    return jmap (value, -30.0, 0.0, -1.0,
                 0.9);
}

double VeNo::Utils::getHigherValue (double a, double b)
{
    return a > b ? a : b;
}

double VeNo::Utils::waveTableMix (double a, double b, double mix)
{
    double diff = 1 - mix;
    a *= diff;
    b *= mix;
    return VeNo::Utils::clamp (a + b, -1, 1);
}

Path VeNo::Utils::drawRectangleWithRadius (int x, int y, int w, int h, float radius, Graphics& g)
{
    Path p;
    p.startNewSubPath (x, y);
    p.lineTo (x + w - radius, y);
    p.addArc (x + w - radius, y, radius, radius, 0.0f, HALF_PI);
    p.lineTo (x + w, y + h - radius);
    p.addArc (x + w - radius, y + h - radius, radius, radius, HALF_PI, PI);
    p.lineTo (x, y + h);
    p.closeSubPath();
    g.fillPath(p);
    return p;
}
