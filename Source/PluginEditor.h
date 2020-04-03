#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "Veno/GUI/LookAndFeel/LookHandler.h"

class VenoAudioProcessorEditor  : public AudioProcessorEditor
{
public:
    VenoAudioProcessorEditor (VenoAudioProcessor&);
    ~VenoAudioProcessorEditor();
    void paint (Graphics&) override;
    void resized() override;

private:
    VenoAudioProcessor& processor;
    std::string id = Uuid().toString().toStdString();
    LookAndFeel_V4 *look = new LookHandler();

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (VenoAudioProcessorEditor)
};
