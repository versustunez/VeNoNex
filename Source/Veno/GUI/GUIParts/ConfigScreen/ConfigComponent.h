//
// Created by versustune on 14.06.20.
//

#ifndef VENO_CONFIGCOMPONENT_H
#define VENO_CONFIGCOMPONENT_H

#include "JuceHeader.h"
#include "../../../Core/Config.h"
#include "../../Components/Config/VeNoColour.h"
#include "../../Components/Config/VenoPreColours.h"

class ConfigComponent : public Component
{
public:
    explicit ConfigComponent(std::string pid);
    ~ConfigComponent() override;
    void paint (Graphics& g) override;
    void resized () override;
protected:
    static ThemeColour getColorForId(int id);
    std::string m_pid;
    std::string m_names[8]{
            "Background", "BackgroundTwo", "Accent", "Accent Two", "Warning", "Clip", "LCD Background", "LCD"
    };
    std::vector<std::unique_ptr<VeNoColour>> m_colors;
    std::unique_ptr<VenoPreColours> m_preColours;
    FlexBox flexBox;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ConfigComponent)
};
#endif //VENO_CONFIGCOMPONENT_H
