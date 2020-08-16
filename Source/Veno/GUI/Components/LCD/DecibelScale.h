//
// Created by Maurice on 29.06.2020.
//

#ifndef VENO_DECIBELSCALE_H
#define VENO_DECIBELSCALE_H

#include "JuceHeader.h"
#include "../BaseComponent.h"

class DecibelScale : public BaseComponent
{
private:
public:
    explicit DecibelScale (const std::string& process_id);
    ~DecibelScale () override = default;
    void resized () override;
    void paint (Graphics& g) override;
    int getScale(float dB);
    void drawLabel(Graphics& g, int y, const std::string& label);
    int m_mode = 0;
protected:
    float m_scale = 0;
    float m_lastY = 0;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DecibelScale)
};


#endif //VENO_DECIBELSCALE_H
