#ifndef VENO_VENOSELECT_H
#define VENO_VENOSELECT_H

#include "JuceHeader.h"
#include "../BaseComponent.h"

typedef AudioProcessorValueTreeState::ComboBoxAttachment ComboBoxAttachment;

class VeNoSelect : public BaseComponent
{
private:
public:
    enum Type
    {
        WaveTable = 0,
        Filter,
        Free,
        DetuneMode,
        LimiterMode,
        NoSelect = 99
    };

    VeNoSelect (const std::string& name, const std::string& pid);

    ~VeNoSelect () override;

    void init (const std::string& label, LabelPosition position, VeNoSelect::Type type);

    void select (int i);

    void addItem (const std::string& item);

    void resized () override;

    void paint (Graphics& g) override;

protected:
    std::unique_ptr<ComboBox> m_select;
    std::unique_ptr<ComboBoxAttachment> m_attachment;
    int m_lastAddItem = 1;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(VeNoSelect)
};


#endif //VENO_VENOSELECT_H
