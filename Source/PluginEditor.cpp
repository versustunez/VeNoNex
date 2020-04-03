#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "Veno/Core/Config.h"

//==============================================================================
VenoAudioProcessorEditor::VenoAudioProcessorEditor(VenoAudioProcessor &p)
        : AudioProcessorEditor(&p), processor(p) {
    Config::getInstance()->registerEditor(this, id);
    LookAndFeel::setDefaultLookAndFeel(look);
    setSize(400, 300);
}

VenoAudioProcessorEditor::~VenoAudioProcessorEditor() {
    LookAndFeel::setDefaultLookAndFeel(nullptr);
    Config::getInstance()->removeEditor(id);
    delete look;
}

//==============================================================================
void VenoAudioProcessorEditor::paint(Graphics &g) {
    g.fillAll(getLookAndFeel().findColour(ResizableWindow::backgroundColourId));
    g.setColour(Colours::white);
    g.setFont(15.0f);
    g.drawFittedText("Hello World!", getLocalBounds(), Justification::centred, 1);
}

void VenoAudioProcessorEditor::resized() {
}
