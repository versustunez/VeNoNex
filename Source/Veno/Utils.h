#ifndef VENO_UTILS_H
#define VENO_UTILS_H

#include "JuceHeader.h"
#include "GUI/Components/BaseComponent.h"

namespace VeNo
{
    class Utils
    {
    public:
        static double DB_GAIN_CONVERSION_MULTIPLIER;
        static int NOTES_PER_OCTAVE;
        static int CENTS_PER_NOTE;
        static int CENTS_PER_OCTAVE;
        static double DOUBLE_PI;
        static double PI;

        Utils () = default;

        ~Utils () = default;

        static double setFontSize (double size, Graphics& g);

        static void setPosition (int width, int height, int x, int y, BaseComponent& component, bool useMarginY);

        static void setPositionSameRow (int width, int height, BaseComponent& component,
                                        BaseComponent& previous);

        static void
        setPositionByPreviousRow (int width, int height, int x, BaseComponent& component, BaseComponent& previous);

        static std::vector<int> calcPosition (int width, int height, int prevWidth, int prevHeight);

        static int getCalculatedWidth (int width);

        static int getCalculatedHeight (int height);

        // audio utils
        static int nextPowerOfTwo (double value);

        static double clamp (double value, double min, double max);

        static double polyBlep (double t, double phaseInc);

        static double lerp (double a, double b, double f);

        static double centsToRatio (double cents);

        static double gainToDb (double gain);

        static double dbToGain (double decibels);

        static double dBForChannel (double value);

        static double getHigherValue (double a, double b);

        static double waveTableMix (double a, double b, double mix);
    };
}
#endif //VENO_UTILS_H
