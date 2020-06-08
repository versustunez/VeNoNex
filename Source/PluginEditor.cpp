#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "Veno/Core/Config.h"

VenoAudioProcessorEditor::VenoAudioProcessorEditor(VenoAudioProcessor &p)
        : AudioProcessorEditor(&p), processor(p) {
    m_id = p.m_id;
    Config::getInstance()->registerEditor(this, m_id);
    LookAndFeel::setDefaultLookAndFeel(m_look);
    setSize(400, 300);
}

VenoAudioProcessorEditor::~VenoAudioProcessorEditor() {
    LookAndFeel::setDefaultLookAndFeel(nullptr);
    Config::getInstance()->removeEditor(m_id);
    delete m_look;
}

void VenoAudioProcessorEditor::paint(Graphics &g) {
    g.fillAll(getLookAndFeel().findColour(ResizableWindow::backgroundColourId));
    g.setColour(Colours::white);
    g.setFont(15.0f);
}

void VenoAudioProcessorEditor::resized() {
}
