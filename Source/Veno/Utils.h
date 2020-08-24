#ifndef VENO_UTILS_H
#define VENO_UTILS_H

#include "JuceHeader.h"

namespace VeNo
{
    class Utils
    {
    public:
        static float DB_GAIN_CONVERSION_MULTIPLIER;
        static int NOTES_PER_OCTAVE;
        static int CENTS_PER_NOTE;
        static int CENTS_PER_OCTAVE;
        static double DOUBLE_PI;
        static double PI;

        Utils () = default;
        ~Utils () = default;
        static float setFontSize (float size, Graphics& g);
        static void
        setPosition (int width, int height, int x, int y, std::shared_ptr<Component>& component, bool useMarginY);
        static void setPositionSameRow (int width, int height, std::shared_ptr<Component>& component,
                                        std::shared_ptr<Component>& previous);
        static void
        setPositionByPreviousRow(int width, int height, int x, std::shared_ptr<Component>& component, std::shared_ptr<Component>& previous);
        static std::vector<int> calcPosition(int width, int height, int prevWidth, int prevHeight);
        static int getCalculatedWidth(int width);
        static int getCalculatedHeight(int height);

        // audio utils
        static int nextPowerOfTwo (float value);
        static float clamp (float value, float min, float max);
        static float polyBlep(float t, float phaseInc);
        static float lerp(float a, float b, float f);
        static float centsToRatio(float cents);
        static float gainToDb(float gain);
        static float dbToGain(float decibels);
        static float dBForChannel(float value);
        static float getHigherValue(float a, float b);
        static float waveTableMix(float a, float b, float mix);
    };
}
#endif //VENO_UTILS_H
