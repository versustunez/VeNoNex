#include "Waveforms.h"
#include <utility>
#include "../../../Core/Config.h"
#include "../../../Utils.h"
#include "../../../VenoInstance.h"
#include "../../../GUI/Fonts/Fonts.h"

#ifdef __APPLE__
#include <GLFW/glfw3.h>
#endif

Waveforms::Waveforms (const std::string& processId) : BaseComponent (processId)
{
    setMouseCursor (MouseCursor::PointingHandCursor);
    setInterceptsMouseClicks (true, false);
    m_context.setOpenGLVersionRequired (OpenGLContext::OpenGLVersion::openGL3_2);
    m_context.setRenderer (this);
    m_context.setContinuousRepainting (false);
    m_context.setComponentPaintingEnabled (true);
    m_context.attachTo (*this);
    std::srand (unsigned (time (nullptr)));
    m_randomText = (std::rand () % RANDOM_TEXT_COUNT);
    m_ticks = 0;
    m_dBScale = std::make_unique<DecibelScale> (processId);
    m_dBScale->m_mode = -1;
    m_fft = std::make_unique<FFT> ();
    addAndMakeVisible (*m_dBScale);
    VenoInstance::getInstance (m_processId)->changeListener->addListener ("waveform", this);
    getState ();
}

Waveforms::~Waveforms ()
{
    VenoInstance::getInstance (m_processId)->changeListener->removeListener ("waveform");
    VenoInstance::getInstance (m_processId)->state->m_lcd_mode = m_mode;
    stopTimer ();
    m_shaderProgram.reset ();
    m_context.detach ();
    m_dBScale.reset (nullptr);
}

void Waveforms::mouseDown (const MouseEvent& e)
{
    if (!m_enableModeToggle)
    {
        return;
    }
    m_mode++;
    if (m_mode > MODE_COUNT)
    {
        m_mode = 0;
    }
    m_dBScale->m_mode = m_mode;
    m_dBScale->repaint ();
}

void Waveforms::mouseDrag (const MouseEvent& e)
{
    //do nothing... you faggot
}

void Waveforms::timerCallback ()
{
    handleAsyncUpdate ();
}

void Waveforms::paint (Graphics& g)
{
    if (!VenoInstance::hasInstance (m_processId))
    {
        return;
    }
    std::shared_ptr<Theme> theme = Config::getInstance ()->getCurrentTheme ();
    auto accent = theme->getColour (ThemeColour::lcd);
    g.setColour (accent);
    g.setFont (*VenoFonts::getLCD ());
    VeNo::Utils::setFontSize (16.0f, g);
    if (m_isStarting)
    {
        g.drawText (m_warmUpText[m_randomText], 0, 0, getWidth (), getHeight (),
                    Justification::centred, true);
        m_ticks++;
        if (m_ticks > m_time_needed)
        {
            m_isStarting = false;
            m_ticks = 0;
            m_needToClear = true;
        }
    }
    else if (m_isChangingData)
    {
        m_dBScale->m_mode = -1;
        m_dBScale->repaint ();
        drawChangedParameter (g, getWidth (), getHeight (), 0, 0);
        m_ticks++;
        if (m_ticks > m_time_needed)
        {
            m_isChangingData = false;
            m_ticks = 0;
            m_needToClear = true;
        }
    }
    else
    {
        if (m_needToClear)
        {
            m_dBScale->m_mode = m_mode;
            m_dBScale->repaint ();
            g.resetToDefaultState ();
            m_needToClear = false;
        }
        g.setFont (*VenoFonts::getLCD ());
        VeNo::Utils::setFontSize (16.0f, g);
        if (m_mode == 0)
        {
            auto instance = VenoInstance::getInstance (BaseComponent::m_processId);
            g.setColour (theme->getColour (ThemeColour::lcd_bg));
            float size = VeNo::Utils::setFontSize (7, g);
            auto halfWidth = getWidth () / 2;
            auto halfHalfWidth = halfWidth / 2;
            auto y = getHeight () - size;
            g.drawText (std::to_string (instance->audioBuffer->leftPeak), halfWidth - halfHalfWidth - (size * 1.5), y,
                        (size * 3), size, Justification::centred, false);
            g.drawText (std::to_string (instance->audioBuffer->rightPeak), halfWidth + halfHalfWidth - (size * 1.5), y,
                        (size * 3), size, Justification::centred, false);
        }
    }
}

void Waveforms::drawChangedParameter (Graphics& g, int w, int h, int x, int y) const
{
    int halfHeight = h / 2;
    float font = VeNo::Utils::setFontSize (12, g);
    g.drawText (m_changedParameter, x, y + halfHeight - font, w, font, Justification::centred, true);
    g.drawText (std::to_string (m_changedValue), x, y + halfHeight + 4, w, font, Justification::centred,
                true);
}

void Waveforms::resized ()
{
    auto halfWidth = getWidth () / 2;
    auto w = VeNo::Utils::getCalculatedWidth (21);
    m_dBScale->setBounds (halfWidth - (w / 2), 0, w, getHeight ());
}

void Waveforms::getState ()
{
    if (VenoInstance::hasInstance (m_processId) && VenoInstance::getInstance (m_processId)->state->m_isFirstEditor)
    {
        VenoInstance::getInstance (m_processId)->state->m_isFirstEditor = false;
        m_isStarting = true;
        startTimer (1000);
    }
    else
    {
        m_mode = VenoInstance::getInstance (m_processId)->state->m_lcd_mode;
        m_dBScale->m_mode = m_mode;
        m_dBScale->repaint ();
        stopTimer ();
    }
}

void Waveforms::parameterChanged (VeNoParameter* parameter)
{
    m_changedParameter = parameter->getShowName ();
    m_changedValue = parameter->getBaseValue ();
    m_isChangingData = true;
    m_ticks = 0;
    startTimer (1000);
}

void Waveforms::notify (const std::string& name, float value)
{
    if (m_mode == 2)
    {
        m_fft->drawNextFrameOfSpectrum (VenoInstance::getInstance (m_processId)->audioBuffer->getBuffer ());
    }

    if (isTimerRunning ())
    {
        return;
    }
    if (!isUpdatePending () && m_mode < 3 && value != m_previous_value)
    {
        m_previous_value = value;
        triggerAsyncUpdate ();
    }
}

void Waveforms::handleAsyncUpdate ()
{
    if (!VenoInstance::hasInstance (m_processId))
    {
        stopTimer ();
        return;
    }
    if (m_isStarting || m_isChangingData || m_needToClear)
    {
        repaint ();
    }
    else
    {
        if (m_context.isAttached ())
        {
            m_context.triggerRepaint ();
            stopTimer ();
        }
    }
}
