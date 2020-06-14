//
// Created by versustune on 08.06.20.
//

#ifndef VENO_UTILS_H
#define VENO_UTILS_H

#include "JuceHeader.h"

namespace VeNo
{
    class Utils
    {
    public:
        Utils () = default;
        ~Utils () = default;
        static int nextPowerOfTwo (float value);
        static float clamp (float value, float min, float max);
        static float setFontSize (float size, Graphics& g);
        static void
        setPosition (int width, int height, int x, int y, std::shared_ptr<Component> component, bool useMarginY);
        static void setPositionSameRow (int width, int height, std::shared_ptr<Component> component,
                                        std::shared_ptr<Component> previous);
        static void
        setPositionByPreviousRow(int width, int height, int x, std::shared_ptr<Component> component, std::shared_ptr<Component> previous);
        static std::vector<int> calcPosition(int width, int height, int prevWidth, int prevHeight);
        static int getCalculatedWidth(int width);
        static int getCalculatedHeight(int height);
    };
}
#endif //VENO_UTILS_H
