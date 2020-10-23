#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "Veno/Utils/Logger.h"
#include "Veno/GUI/Fonts/Fonts.h"
#include "Veno/Utils.h"

#define SIDEBAR_WIDTH 300
#define KEYBOARD_HEIGHT 100
#define FOOTER_BG_HEIGHT 110

VenoAudioProcessorEditor::VenoAudioProcessorEditor (VenoAudioProcessor& p)
        : AudioProcessorEditor (&p), processor (p), m_id (p.m_id)
{
    Config::getInstance ()->registerEditor (this, m_id);
    VenoInstance::getInstance (m_id)->glContext = &m_openGLContext;
    m_sidebar = std::make_unique<Sidebar> (m_id);
    m_keyboard = std::make_unique<VeNoKeyboard> (m_id);
    m_pitchDown = std::make_unique<VeNoKnob> ("pitchbend__down", m_id);
    m_pitchUp = std::make_unique<VeNoKnob> ("pitchbend__up", m_id);
    m_legato = std::make_unique<VeNoCheck> ("mono_legato", "Mono Legato", m_id);
    m_porta = std::make_unique<VeNoKnob> ("portamento", m_id);
    m_porta->init ("Portamento");
    m_pitchDown->init ("Bend Down");
    m_pitchUp->init ("Bend Up");
    m_tabber = std::make_unique<VeNo::Tabber> (m_id);
    setSize (1200 * Config::getInstance ()->getScale (), 700 * Config::getInstance ()->getScale ());
    addAndMakeVisible (*m_sidebar);
    addAndMakeVisible (*m_keyboard);
    addAndMakeVisible (*m_tabber);
    addAndMakeVisible (*m_pitchDown);
    addAndMakeVisible (*m_pitchUp);
    addAndMakeVisible (*m_legato);
    addAndMakeVisible (*m_porta);
    m_openGLContext.setRenderer (this);
    m_openGLContext.setContinuousRepainting (false);
    m_openGLContext.setComponentPaintingEnabled (true);
    m_openGLContext.attachTo (*this);
    m_openGLContext.makeActive ();
}

VenoAudioProcessorEditor::~VenoAudioProcessorEditor ()
{
    LookAndFeel::setDefaultLookAndFeel (nullptr);
    m_sidebar.reset (nullptr);
    m_keyboard.reset (nullptr);
    m_tabber.reset (nullptr);
    VenoInstance::getInstance (m_id)->glContext = nullptr;
    m_openGLContext.detach ();
    Config::getInstance ()->removeEditor (m_id);
}

void VenoAudioProcessorEditor::paint (Graphics& g)
{
    auto theme = Config::getInstance ()->getCurrentTheme ();
    g.setFont (*VenoFonts::getNormal ());
    g.fillAll (theme->getColour (ThemeColour::bg));
    g.setColour (theme->getColour (ThemeColour::bg));
    int sidebarWidth = VeNo::Utils::getScaledSize (SIDEBAR_WIDTH);
    int footerHeight = VeNo::Utils::getScaledSize (FOOTER_BG_HEIGHT);
    g.fillRect (0, 0, sidebarWidth, getHeight ());
    g.setColour (theme->getColour (ThemeColour::bg).withAlpha (0.7f));
    g.fillRect (sidebarWidth, getHeight () - footerHeight, getWidth () - sidebarWidth, footerHeight);
    g.setColour (theme->getColour (ThemeColour::font));
}

void VenoAudioProcessorEditor::resized ()
{
    int sidebarWidth = VeNo::Utils::getScaledSize (SIDEBAR_WIDTH);
    if (m_sidebar != nullptr)
    {
        m_sidebar->setBounds (0, 0, sidebarWidth, getHeight ());
    }
    int keyboardHeight = VeNo::Utils::getScaledSize (KEYBOARD_HEIGHT);
    int footerY = getHeight () - keyboardHeight;
    if (m_keyboard != nullptr)
    {
        auto knobW = VeNo::Utils::getScaledSize (110);
        auto knobH = VeNo::Utils::getScaledSize (42);
        m_pitchUp->setBounds (sidebarWidth, footerY + VeNo::Utils::getScaledSize (5), knobW, knobH);
        m_pitchDown->setBounds (sidebarWidth, footerY + VeNo::Utils::getScaledSize (50), knobW, knobH);
        m_keyboard->setBounds (VeNo::Utils::getScaledSize (SIDEBAR_WIDTH + 110), footerY,
                               VeNo::Utils::getScaledSize (675), keyboardHeight);

        m_legato->setBounds (
                VeNo::Utils::getScaledSize (SIDEBAR_WIDTH + 802),
                footerY + VeNo::Utils::getScaledSize (10),
                VeNo::Utils::getScaledSize (80),
                VeNo::Utils::getScaledSize (30)
        );
        m_porta->setBounds (VeNo::Utils::getScaledSize (SIDEBAR_WIDTH + 790), footerY + VeNo::Utils::getScaledSize (50),
                            knobW, knobH);
    }

    if (m_tabber != nullptr)
    {
        m_tabber->setBounds (sidebarWidth, 0, getWidth () - sidebarWidth, getHeight () - keyboardHeight);
    }
}

void VenoAudioProcessorEditor::updateTabs ()
{
    m_tabber->updateColour ();
    m_tabber->updateSize ();
}

void VenoAudioProcessorEditor::newOpenGLContextCreated ()
{
    m_sidebar->getWaveform ()->newOpenGLContextCreated ();
}

void VenoAudioProcessorEditor::renderOpenGL ()
{
    auto knobs = VenoInstance::getInstance (m_id)->state->componentStates.m_knobs;
    for (auto& knob : knobs)
    {
        if (knob.second->isVisible ())
        {
            knob.second->repaint ();
        }
    }
}

void VenoAudioProcessorEditor::openGLContextClosing ()
{

}
