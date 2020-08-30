#include "SidebarLCD.h"
#include "../../../Utils.h"
#include "../../../Core/Config.h"
#include "../../../GUI/Fonts/Fonts.h"

SidebarLCD::SidebarLCD (const std::string& process_id) : BaseComponent (process_id)
{
    m_waveform = std::make_shared<Waveforms> (process_id);
    addAndMakeVisible (*m_waveform);

    m_configButton = std::make_unique<VeNoActionButton> (process_id, "Config", VeNoActionButton::ButtonType::Config);
    m_debugButton = std::make_unique<VeNoActionButton> (process_id, "Debug", VeNoActionButton::ButtonType::Debug);
    m_matrixButton = std::make_unique<VeNoActionButton> (process_id, "Matrix", VeNoActionButton::ButtonType::Matrix);
    m_presetManager = std::make_unique<VeNoActionButton> (process_id, "Preset", VeNoActionButton::ButtonType::Presets);
    addAndMakeVisible (*m_configButton);
    addAndMakeVisible (*m_debugButton);
    addAndMakeVisible (*m_matrixButton);
    addAndMakeVisible (*m_presetManager);
}

SidebarLCD::~SidebarLCD ()
{
    m_configButton.reset ();
    m_debugButton.reset ();
    m_presetManager.reset ();
    m_matrixButton.reset ();
    m_waveform.reset ();
}

void SidebarLCD::drawHeadline (Graphics& g)
{
    float fontSize = VeNo::Utils::setFontSize (12.0f, g) + 2;
    int line = fontSize + 2;
    // should draw random stuff? or draw current selected preset :)
    g.drawText ("LICENSED TO: " + SystemStats::getLogonName (), 0, 2, getWidth (), fontSize,
                Justification::centred,
                true);
    g.drawLine (0, line, getWidth (), line);
}

void SidebarLCD::drawFooter (Graphics& g)
{
    float fontSize = VeNo::Utils::setFontSize (12.0f, g) + 4;
    int line = getHeight () - fontSize;
    g.drawLine (0, line - 4, getWidth (), line - 4);
}

void SidebarLCD::resized ()
{
    float size = (12 * Config::getInstance ()->getScale ()) + 4;
    if (m_waveform != nullptr)
    {
        m_waveform->setBounds (0, size * 2, getWidth (), getHeight () - (size * 4));
    }

    auto x = getWidth () / 4;
    auto y = getHeight () - size;
    m_configButton->setBounds (0, y, x, size);
    m_matrixButton->setBounds (x, y, x, size);
    m_presetManager->setBounds (x * 2, y, x, size);
    m_debugButton->setBounds (x * 3, y, x, size);
}

void SidebarLCD::paint (Graphics& g)
{
    std::shared_ptr<Theme> theme = Config::getInstance ()->getCurrentTheme ();
    auto colour = theme->getColour (ThemeColour::lcd_bg);
    g.fillAll (colour);
    // background
    auto accent = theme->getColour (ThemeColour::lcd);
    g.setColour (accent);
    g.setFont (*VenoFonts::getLCD ());
    drawHeadline (g);
    drawFooter (g);
}

std::shared_ptr<Waveforms> SidebarLCD::getWaveform ()
{
    return m_waveform;
}
