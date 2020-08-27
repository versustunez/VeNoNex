#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "Veno/GUI/LookAndFeel/LookHandler.h"
#include "Veno/GUI/GUIParts/Sidebar/Sidebar.h"
#include "Veno/GUI/Components/VeNoKeyboard.h"

class VenoAudioProcessorEditor : public AudioProcessorEditor
{
public:
    VenoAudioProcessorEditor (VenoAudioProcessor&);

    ~VenoAudioProcessorEditor ();

    void paint (Graphics&) override;

    void resized () override;

private:
    VenoAudioProcessor& processor;
    std::string m_id;
    LookAndFeel_V4* m_look = new LookHandler ();
    std::unique_ptr<VeNoKeyboard> m_keyboard;
    std::unique_ptr<Sidebar> m_sidebar;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (VenoAudioProcessorEditor)
};
