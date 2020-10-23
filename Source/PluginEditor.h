#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "Veno/GUI/LookAndFeel/LookHandler.h"
#include "Veno/GUI/GUIParts/Sidebar/Sidebar.h"
#include "Veno/GUI/Components/VeNoKeyboard.h"
#include "Veno/GUI/GUIParts/Pages/Tabber.h"

class VenoAudioProcessorEditor : public AudioProcessorEditor, public OpenGLRenderer
{
public:
    VenoAudioProcessorEditor (VenoAudioProcessor&);

    ~VenoAudioProcessorEditor ();

    void paint (Graphics&) override;

    void resized () override;

    void updateTabs();

    void newOpenGLContextCreated () override;

    void renderOpenGL () override;

    void openGLContextClosing () override;

private:
    VenoAudioProcessor& processor;
    std::string m_id;
    std::unique_ptr<VeNoKeyboard> m_keyboard;
    std::unique_ptr<VeNoKnob> m_pitchDown;
    std::unique_ptr<VeNoKnob> m_pitchUp;
    std::unique_ptr<VeNoCheck> m_legato;
    std::unique_ptr<VeNoKnob> m_porta;
    std::unique_ptr<Sidebar> m_sidebar;
    std::unique_ptr<VeNo::Tabber> m_tabber;
    OpenGLContext m_openGLContext;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (VenoAudioProcessorEditor)
};
