#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "Veno/Utils/Logger.h"
#include "Veno/Fonts/Fonts.h"

#define SIDEBAR_WIDTH 300

VenoAudioProcessorEditor::VenoAudioProcessorEditor (VenoAudioProcessor& p)
        : AudioProcessorEditor(&p), processor(p)
{
    m_id = p.m_id;
    Config::getInstance()->registerEditor(this, m_id);
    LookAndFeel::setDefaultLookAndFeel(m_look);
    m_sidebar = std::make_unique<Sidebar>(m_id);
    setSize(1200 * Config::getInstance()->getScale(), 700 * Config::getInstance()->getScale());
    addAndMakeVisible(*m_sidebar);
    VenoInstance::getInstance(m_id)->handler->registerListener("waveForm", m_sidebar->getWaveform().get());
}

VenoAudioProcessorEditor::~VenoAudioProcessorEditor ()
{
    VenoInstance::getInstance(m_id)->handler->deleteListener("waveForm");
    LookAndFeel::setDefaultLookAndFeel(nullptr);
    m_sidebar.reset(nullptr);
    delete m_look;
    Config::getInstance()->removeEditor(m_id);
}

void VenoAudioProcessorEditor::paint (Graphics& g)
{
    auto theme = Config::getInstance()->getCurrentTheme();
    g.setFont(*VenoFonts::getNormal());
    g.fillAll(theme->getColour(ThemeColour::bg_two));
    g.setColour(theme->getColour(ThemeColour::bg));
    g.fillRect(0, 0, VeNo::Utils::getCalculatedWidth(SIDEBAR_WIDTH), getHeight());
    g.setColour(theme->getColour(ThemeColour::accent));
}

void VenoAudioProcessorEditor::resized ()
{
    if (m_sidebar != nullptr)
    {
        m_sidebar->setBounds(0, 0, VeNo::Utils::getCalculatedWidth(SIDEBAR_WIDTH), getHeight());
    }
}
