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
    LookAndFeel::setDefaultLookAndFeel (m_look);
    m_sidebar = std::make_unique<Sidebar> (m_id);
    m_keyboard = std::make_unique<VeNoKeyboard> (m_id);
    setSize (1200 * Config::getInstance ()->getScale (), 700 * Config::getInstance ()->getScale ());
    addAndMakeVisible (*m_sidebar);
    addAndMakeVisible (*m_keyboard);
}

[[noreturn]] VenoAudioProcessorEditor::~VenoAudioProcessorEditor ()
{
    LookAndFeel::setDefaultLookAndFeel (nullptr);
    m_sidebar.reset (nullptr);
    m_keyboard.reset (nullptr);
    delete m_look;
    Config::getInstance ()->removeEditor (m_id);
}

void VenoAudioProcessorEditor::paint (Graphics& g)
{
    auto theme = Config::getInstance ()->getCurrentTheme ();
    g.setFont (*VenoFonts::getNormal ());
    g.fillAll (theme->getColour (ThemeColour::bg_two));
    g.setColour (theme->getColour (ThemeColour::bg));
    int sidebarWidth = VeNo::Utils::getCalculatedWidth (SIDEBAR_WIDTH);
    int footerHeight = VeNo::Utils::getCalculatedHeight (FOOTER_BG_HEIGHT);
    g.fillRect (0, 0, sidebarWidth, getHeight ());
    g.setColour (theme->getColour (ThemeColour::bg).withAlpha (0.7f));
    g.fillRect (sidebarWidth, getHeight () - footerHeight, getWidth () - sidebarWidth, footerHeight);
    g.setColour (theme->getColour (ThemeColour::font));
}

void VenoAudioProcessorEditor::resized ()
{
    float sidebarWidth = VeNo::Utils::getCalculatedWidth (SIDEBAR_WIDTH);
    if (m_sidebar != nullptr)
    {
        m_sidebar->setBounds (0, 0, sidebarWidth, getHeight ());
    }
    float keyboardHeight = VeNo::Utils::getCalculatedHeight (KEYBOARD_HEIGHT);
    if (m_keyboard != nullptr)
    {
        float keyboardWidth = (getWidth () - sidebarWidth) * 0.75;
        float spacer = ((getWidth () - sidebarWidth) * 0.25) * 0.5;
        m_keyboard->setBounds (sidebarWidth + spacer, getHeight () - keyboardHeight, keyboardWidth,
                               keyboardHeight);
    }
}
