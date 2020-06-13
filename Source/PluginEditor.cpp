#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "Veno/Core/Config.h"
#include "Veno/Utils/Logger.h"
#include "Veno/Fonts/Fonts.h"

VenoAudioProcessorEditor::VenoAudioProcessorEditor(VenoAudioProcessor &p)
        : AudioProcessorEditor(&p), processor(p) {
    m_id = p.m_id;
    Config::getInstance()->registerEditor(this, m_id);
    LookAndFeel::setDefaultLookAndFeel(m_look);
    waveform = std::make_unique<SidebarLCD>(m_id);
    setSize(600, 400);
    addAndMakeVisible(*waveform);
}

VenoAudioProcessorEditor::~VenoAudioProcessorEditor() {
    LookAndFeel::setDefaultLookAndFeel(nullptr);
    waveform.reset(nullptr);
    delete m_look;
    Config::getInstance()->removeEditor(m_id);
}

void VenoAudioProcessorEditor::paint(Graphics &g) {
    g.setFont(VenoFonts::getNormal());
    g.fillAll(Colour(0, 0, 0));
}

void VenoAudioProcessorEditor::resized() {
    if (waveform != nullptr) {
        waveform->setBounds(0, 0, getWidth(), getHeight());
    }
}
