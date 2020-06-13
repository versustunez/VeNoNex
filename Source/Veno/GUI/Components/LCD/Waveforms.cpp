//
// Created by versustune on 11.06.20.
//

#include "Waveforms.h"
#include <utility>
#include "../../../Core/Config.h"
#include "../../../Utils.h"
#include "../../../VenoInstance.h"
#include "../../../Fonts/Fonts.h"

Waveforms::Waveforms (const std::string& processId) : BaseComponent (processId)
{
    m_context.setOpenGLVersionRequired (OpenGLContext::OpenGLVersion::openGL3_2);
    m_context.setRenderer (this);
    m_context.setContinuousRepainting (false);
    m_context.setComponentPaintingEnabled (true);
    m_context.attachTo (*this);
    auto fps = Config::getInstance ()->getFps ();
    startTimerHz (Config::getInstance ()->getFps ());
    std::srand (unsigned (time (nullptr)));
    pickRandomText = (std::rand () % RANDOM_TEXT_COUNT);
    m_ticks = 0;
    // is something that
    m_time_needed = roundToInt (4000 / (1000 / fps));
    m_time_needed_startup = roundToInt (1000 / (1000 / fps));
}

Waveforms::~Waveforms ()
{
    stopTimer ();
    shaderProgram.reset ();
    m_context.detach ();
}

void Waveforms::newOpenGLContextCreated ()
{
    compileOpenGLShaderProgram ();
}

void Waveforms::openGLContextClosing ()
{

}

void Waveforms::renderOpenGL ()
{
    if (!isShowing () || shaderProgram == nullptr || !shaderProgram->getLastError ().isEmpty ())
    {
        return;
    }
    auto theme = Config::getInstance ()->getCurrentTheme ();
    if (theme == nullptr)
    {
        return;
    }
    glViewport (0, 0, getWidth (), getHeight ());
    OpenGLHelpers::clear (theme->getColour (ThemeColour::lcd_bg));
    glEnable (GL_BLEND);
    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    shaderProgram->use ();
    auto color = theme->getColour (ThemeColour::lcd);
    shaderProgram->setUniform ("color", color.getFloatRed (), color.getFloatGreen (), color.getFloatBlue (),
                               color.getFloatAlpha ());
    if (m_isWelcome || m_isStarting || m_isChangingData)
    {
        return;
    }
    switch (m_mode)
    {
        case 1:
            drawAudioOutput ();
            break;
        case 2:
            drawWaveTable ();
            break;
        case 3:
            drawSpectrum ();
            break;
        default:
            drawPeakMeter ();
    }
}

void Waveforms::handleAsyncUpdate ()
{

}

void Waveforms::compileOpenGLShaderProgram ()
{
    std::unique_ptr<OpenGLShaderProgram> shaderProgramAttempt
            = std::make_unique<OpenGLShaderProgram> (m_context);
    if (shaderProgramAttempt->addVertexShader ({BinaryData::WaveForm_vertex_glsl})
        && shaderProgramAttempt->addFragmentShader ({BinaryData::WaveForm_fragment_glsl})
        && shaderProgramAttempt->link ())
    {
        shaderProgram = std::move (shaderProgramAttempt);
    }
}

void Waveforms::mouseDown (const MouseEvent& e)
{
    if (!m_enableModeToggle)
    {
        return;
    }
    m_mode++;
    if (m_mode > 3)
    {
        m_mode = 0;
    }
}

void Waveforms::mouseDrag (const MouseEvent& e)
{
    //do nothing... you faggot
}

void Waveforms::timerCallback ()
{
    if (m_isWelcome || m_isStarting || m_isChangingData || needToClear)
    {
        repaint ();
    }
    else
    {
        if (m_context.isAttached ())
        {
            m_context.triggerRepaint ();
        }
    }
}

void Waveforms::drawWaveTable ()
{
    // this will draw the current selected oscillator :D
}

void Waveforms::drawAudioOutput ()
{
    // draw audio from the oscillators
    auto instance = VenoInstance::getInstance (BaseComponent::m_processId);
    auto buffer = instance->audioBuffer->getBuffer ();
    glBegin (GL_LINE_STRIP);
    float posX = -1;
    float inc = 2.0f / buffer.size ();
    for (float i : buffer)
    {
        glVertex2f (posX, i);
        posX += inc;
    }
    glEnd ();
}

void Waveforms::drawPeakMeter ()
{
    auto theme = Config::getInstance ()->getCurrentTheme ();
    if (theme == nullptr)
    {
        return;
    }
    auto instance = VenoInstance::getInstance (BaseComponent::m_processId);
    instance->audioBuffer->calcPeak ();
    // draw peak signal
    auto leftChannel = jmap (Decibels::gainToDecibels (instance->audioBuffer->leftPeak, -80.0f), -80.0f, 6.0f, -1.0f,
                             1.0f);
    selectColourByPeak (leftChannel);
    glBegin (GL_TRIANGLES);
    glVertex2f (-0.9f, leftChannel);
    glVertex2f (-0.9f, -1.0f);
    glVertex2f (-0.01f, -1.0f);
    glVertex2f (-0.9f, leftChannel);
    glVertex2f (-0.01f, leftChannel);
    glVertex2f (-0.01f, -1.0f);
    glEnd ();
    auto rightChannel = jmap (Decibels::gainToDecibels (instance->audioBuffer->rightPeak, -80.0f), -80.0f, 6.0f, -1.0f,
                              1.0f);
    selectColourByPeak (rightChannel);
    glBegin (GL_TRIANGLES);
    glVertex2f (0.9f, rightChannel);
    glVertex2f (0.9f, -1.0f);
    glVertex2f (0.01f, -1.0f);
    glVertex2f (0.9f, rightChannel);
    glVertex2f (0.01f, rightChannel);
    glVertex2f (0.01f, -1.0f);
    glEnd ();
}

void Waveforms::paint (Graphics& g)
{
    std::shared_ptr<Theme> theme = Config::getInstance ()->getCurrentTheme ();
    auto accent = theme->getColour (ThemeColour::lcd);
    g.setColour (accent);
    g.setFont (*VenoFonts::getLCD ());
    VeNo::Utils::setFontSize (16.0f, g);
    if (m_isWelcome)
    {
        drawWelcome (g, getWidth (), getHeight (), 0, 0);
        m_ticks++;
        if (m_ticks > m_time_needed_startup)
        {
            m_isWelcome = false;
            m_ticks = 0;
            needToClear = true;
        }
    }
    else if (m_isStarting)
    {
        g.drawText (m_warmUpText[pickRandomText], 0, 0, getWidth (), getHeight (),
                    Justification::centred, true);
        m_ticks++;
        if (m_ticks > m_time_needed_startup)
        {
            m_isStarting = false;
            m_ticks = 0;
            needToClear = true;
        }
    }
    else if (m_isChangingData)
    {
        drawChangedParameter (g, getWidth (), getHeight (), 0, 0);
        m_ticks++;
        if (m_ticks > m_time_needed)
        {
            m_isChangingData = false;
            m_ticks = 0;
            needToClear = true;
        }
    }
    else
    {
        g.resetToDefaultState ();
        needToClear = false;
    }
}

void Waveforms::drawChangedParameter (Graphics& g, int w, int h, int x, int y) const
{
    int halfHeight = h / 2;
    float font = VeNo::Utils::setFontSize (12, g);
    g.drawText (changingParameter, x, y + halfHeight - font, w, font, Justification::centred, true);
    g.drawText (std::to_string (changedValue), x, y + halfHeight + 4, w, font, Justification::centred,
                true);
}

void Waveforms::drawWelcome (Graphics& g, int w, int h, int x, int y)
{
    float font = VeNo::Utils::setFontSize (12, g);
    int halfHeight = h / 2;
    g.drawText (m_readyText, x, y + halfHeight - font, w, font, Justification::centred, true);
    g.drawText (SystemStats::getLogonName (), x, y + halfHeight + 4, w, font, Justification::centred,
                true);
}

void Waveforms::drawSpectrum ()
{
}

void Waveforms::selectColourByPeak (float value)
{
    auto theme = Config::getInstance ()->getCurrentTheme ();
    if (theme == nullptr)
    {
        return;
    }
    auto color = theme->getColour (ThemeColour::lcd);
    if (value > 0.8 && value < 0.9)
    {
        color = theme->getColour (ThemeColour::warning);
    }
    if (value > 0.9)
    {
        color = theme->getColour (ThemeColour::clip);
    }
    shaderProgram->setUniform ("color", color.getFloatRed (), color.getFloatGreen (), color.getFloatBlue (),
                               color.getFloatAlpha ());
}
