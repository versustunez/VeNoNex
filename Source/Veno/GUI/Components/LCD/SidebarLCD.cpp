#include "SidebarLCD.h"
#include "../../../Utils.h"
#include "../../../Core/Config.h"
#include "../../../GUI/Fonts/Fonts.h"
#include "../../../VenoInstance.h"

SidebarLCD::SidebarLCD (const std::string& process_id) : BaseComponent (process_id),
                                                         m_waveform (
                                                                 std::make_shared<VeNo::WaveFormsGui> (m_processId)),
                                                         m_dBScale (std::make_unique<DecibelScale> (m_processId)),
                                                         m_parameterScreen (
                                                                 std::make_unique<VeNo::LCDParameters> (m_processId)),
                                                         m_configButton (
                                                                 std::make_unique<VeNoActionButton> (m_processId,
                                                                                                     "Config",
                                                                                                     VeNoActionButton::ButtonType::Config)),
                                                         m_matrixButton (
                                                                 std::make_unique<VeNoActionButton> (m_processId,
                                                                                                     "Matrix",
                                                                                                     VeNoActionButton::ButtonType::Matrix)),
                                                         m_debugButton (std::make_unique<VeNoActionButton> (m_processId,
                                                                                                            "Debug",
                                                                                                            VeNoActionButton::ButtonType::Debug)),
                                                         m_presetManager (
                                                                 std::make_unique<VeNoActionButton> (m_processId,
                                                                                                     "Preset",
                                                                                                     VeNoActionButton::ButtonType::Presets))
{
    setMouseCursor (MouseCursor::PointingHandCursor);
    m_waveform->addMouseListener (this, true);
    m_dBScale->addMouseListener (this, true);
    m_parameterScreen->addMouseListener (this, true);
    addAndMakeVisible (*m_waveform);
    addAndMakeVisible (*m_configButton);
    addAndMakeVisible (*m_debugButton);
    addAndMakeVisible (*m_matrixButton);
    addAndMakeVisible (*m_presetManager);
    addAndMakeVisible (*m_dBScale);
    addChildComponent(*m_parameterScreen);
    VenoInstance::getInstance (m_processId)->changeListener->addListener ("waveform", this);
    getState ();
}

SidebarLCD::~SidebarLCD ()
{
    VenoInstance::getInstance (m_processId)->changeListener->removeListener ("waveform");
    m_configButton.reset ();
    m_debugButton.reset ();
    m_presetManager.reset ();
    m_matrixButton.reset ();
    m_waveform.reset ();
    m_parameterScreen.reset ();
    m_dBScale.reset ();
}

void SidebarLCD::drawHeadline (Graphics& g)
{
    double fontSize = VeNo::Utils::setFontSize (12.0f, g) + 2;
    int line = fontSize + 2;
    g.drawText ("LICENSED TO: " + SystemStats::getFullUserName (), 0, 2, getWidth (), fontSize,
                juce::Justification::centred,
                true);
    g.drawLine (0, line, getWidth (), line);
}

void SidebarLCD::drawFooter (Graphics& g)
{
    double fontSize = VeNo::Utils::setFontSize (12.0f, g) + 4;
    int line = getHeight () - fontSize;
    g.drawLine (0, line - 4, getWidth (), line - 4);
}

void SidebarLCD::resized ()
{
    double size = (12 * Config::getInstance ()->getScale ()) + 4;
    if (m_waveform != nullptr)
    {
        m_waveform->setBounds (0, size * 2, getWidth (), getHeight () - (size * 4));
        auto halfWidth = getWidth () / 2;
        auto w = VeNo::Utils::getScaledSize (21);
        m_dBScale->setBounds (halfWidth - (w / 2), size * 2, w, getHeight () - (size * 4));
        m_parameterScreen->setBounds (0, size * 2, getWidth (), getHeight () - (size * 4));
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

void SidebarLCD::parameterChanged (VeNoParameter* parameter)
{
    if (parameter == nullptr)
        return;

    if (!m_needClear)
    {
        m_parameterScreen->setVisible (true);
    }
    m_parameterScreen->parameterChanged (parameter);
    m_needClear = true;
}

void SidebarLCD::notify (const std::string& name, double value)
{
    m_lastNotifyValue = value;
    if (!isUpdatePending ())
    {
        triggerAsyncUpdate ();
    }
}

void SidebarLCD::handleAsyncUpdate ()
{
    if (m_parameterScreen->m_isChangingData || m_parameterScreen->m_isStarting)
    {
        return;
    }
    m_waveform->updatePaths (m_lastNotifyValue);
    // only redraw all if m_needClear is needed!
    if (m_needClear)
    {
        m_parameterScreen->setVisible (false);
        repaint ();
        m_needClear = false;
        return;
    }
    m_dBScale->repaint ();
    m_waveform->repaint ();
}

void SidebarLCD::getState ()
{
    if (VenoInstance::hasInstance (m_processId) && VenoInstance::getInstance (m_processId)->state->m_isFirstEditor)
    {
        VenoInstance::getInstance (m_processId)->state->m_isFirstEditor = false;
        m_parameterScreen->setVisible(true);
        m_parameterScreen->setIsStarting ();
        m_mode = 0;
        m_dBScale->m_mode = 0;
        m_waveform->mode = 0;
        m_dBScale->repaint ();
        m_needClear = true;
    }
    else
    {
        m_mode = VenoInstance::getInstance (m_processId)->state->m_lcd_mode;
        m_dBScale->m_mode = m_mode;
        m_dBScale->repaint ();
        m_waveform->mode = m_mode;
    }
}

void SidebarLCD::mouseDown (const MouseEvent& event)
{
    m_mode++;
    if (m_mode > 4)
    {
        m_mode = 0;
    }
    VenoInstance::getInstance (m_processId)->state->m_lcd_mode = m_mode;
    m_waveform->mode = m_mode;
    m_dBScale->m_mode = m_mode;
    m_dBScale->repaint ();
}
