#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "Veno/GUI/LookAndFeel/LookHandler.h"
#include "Veno/GUI/Components/LCD/SidebarLCD.h"

class VenoAudioProcessorEditor : public AudioProcessorEditor
{
public:
    VenoAudioProcessorEditor (VenoAudioProcessor&);
    ~VenoAudioProcessorEditor ();
    void paint (Graphics&) override;
    void resized () override;
private:
    VenoAudioProcessor& processor;
    std::string m_id = "";
    LookAndFeel_V4* m_look = new LookHandler ();
    std::unique_ptr<SidebarLCD> waveform;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (VenoAudioProcessorEditor)
};
