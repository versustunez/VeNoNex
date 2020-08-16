//
// Created by versustune on 14.06.20.
//

#ifndef VENO_VENOCOLOUR_H
#define VENO_VENOCOLOUR_H

#include "JuceHeader.h"
#include "../BaseComponent.h"
#include "../../Theme/Theme.h"

class VeNoColour : public BaseComponent, ChangeListener
{
private:
    ThemeColour m_index;
    std::unique_ptr<ColourSelector> m_selector;
    std::string m_name;
public:
    explicit VeNoColour (const std::string& processId, ThemeColour index);
    ~VeNoColour () override;
    void setName(std::string name);
    void resized () override;
    void paint (Graphics& g) override;
protected:
    void changeListenerCallback (ChangeBroadcaster* source) override;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (VeNoColour)
};
#endif //VENO_VENOCOLOUR_H
