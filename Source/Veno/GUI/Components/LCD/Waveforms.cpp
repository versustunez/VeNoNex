//
// Created by versustune on 11.06.20.
//

#include "Waveforms.h"
#include <utility>
#include "../../../Core/Config.h"
#include "../../../Utils.h"
#include "../../../VenoInstance.h"
#include "../../../Fonts/Fonts.h"

#ifdef __APPLE__
#include <GLFW/glfw3.h>
#endif

Waveforms::Waveforms(const std::string& processId) : BaseComponent(processId)
{
    getState();
    setMouseCursor(MouseCursor::PointingHandCursor);
    m_context.setOpenGLVersionRequired(OpenGLContext::OpenGLVersion::openGL3_2);
    m_context.setRenderer(this);
    m_context.setContinuousRepainting(false);
    m_context.setComponentPaintingEnabled(true);
    m_context.attachTo(*this);
    setFps();
    std::srand(unsigned(time(nullptr)));
    m_randomText = (std::rand() % RANDOM_TEXT_COUNT);
    m_ticks = 0;
    m_dBScale = std::make_unique<DecibelScale>(processId);
    m_dBScale->m_mode = -1;
    addAndMakeVisible(*m_dBScale);
}

Waveforms::~Waveforms()
{
    stopTimer();
    m_shaderProgram.reset();
    m_context.detach();
    m_dBScale.reset(nullptr);
}

void Waveforms::newOpenGLContextCreated()
{
    compileOpenGLShaderProgram();
}

void Waveforms::openGLContextClosing()
{

}

void Waveforms::renderOpenGL()
{
    if (!VenoInstance::hasInstance(m_processId) || !m_context.isActive() || !m_context.isAttached() || m_shaderProgram == nullptr || !m_shaderProgram->getLastError().isEmpty())
    {
        stopTimer();
        return;
    }

    if (!isShowing())
    {
        return;
    }

    auto theme = Config::getInstance()->getCurrentTheme();
    if (theme == nullptr)
    {
        return;
    }
    OpenGLHelpers::clear(theme->getColour(ThemeColour::lcd_bg));
    //glViewport(0, 0, getWidth(), getHeight());
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    m_shaderProgram->use();
    auto color = theme->getColour(ThemeColour::lcd);
    m_shaderProgram->setUniform("color", color.getFloatRed(), color.getFloatGreen(), color.getFloatBlue(),
                                color.getFloatAlpha());
    // same color currently! will set to a diff if peak is detected!
    m_shaderProgram->setUniform("gradientColor", color.getFloatRed(), color.getFloatGreen(), color.getFloatBlue(),
                                color.getFloatAlpha());
    if (m_isWelcome || m_isStarting || m_isChangingData)
    {
        return;
    }
    switch (m_mode)
    {
        case 1:
            drawAudioOutput();
            break;
        case 2:
            drawWaveTable();
            break;
        case 3:
            drawSpectrum();
            break;
        default:
            drawPeakMeter();
    }
}

void Waveforms::compileOpenGLShaderProgram()
{
    std::unique_ptr<OpenGLShaderProgram> shaderProgramAttempt
            = std::make_unique<OpenGLShaderProgram>(m_context);
    if (shaderProgramAttempt->addVertexShader({BinaryData::WaveForm_vertex_glsl})
        && shaderProgramAttempt->addFragmentShader({BinaryData::WaveForm_fragment_glsl})
        && shaderProgramAttempt->link())
    {
        m_shaderProgram = std::move(shaderProgramAttempt);
    }
    else
    {
        DBG(shaderProgramAttempt->getLastError().toStdString());
    }
}

void Waveforms::mouseDown(const MouseEvent& e)
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
    m_dBScale->m_mode = m_mode;
    m_dBScale->repaint();
}

void Waveforms::mouseDrag(const MouseEvent& e)
{
    //do nothing... you faggot
}

void Waveforms::timerCallback()
{
    if (!VenoInstance::hasInstance(m_processId))
    {
        stopTimer();
        return;
    }
    if (m_isWelcome || m_isStarting || m_isChangingData || m_needToClear)
    {
        repaint();
    }
    else
    {
        if (m_context.isAttached())
        {
            m_context.triggerRepaint();
        }
    }
    setFps();
}

void Waveforms::drawWaveTable()
{
    // this will draw the current selected oscillator :D
}

void Waveforms::drawAudioOutput()
{
    // draw audio from the oscillators
    auto instance = VenoInstance::getInstance(BaseComponent::m_processId);
    auto buffer = instance->audioBuffer->getBuffer();
    glBegin(GL_LINE_STRIP);
    float posX = -1;
    float inc = 2.0f / buffer.size();
    for (float j : buffer)
    {
        try
        {
            glVertex2f(posX, j);
            posX += inc;
        } catch (std::exception &e)
        {
            DBG(e.what());
            //something is wrong skip the draw and end it!
            break;
        }
    }
    glEnd();
}

void Waveforms::drawPeakMeter()
{
    auto theme = Config::getInstance()->getCurrentTheme();
    if (theme == nullptr)
    {
        return;
    }
    auto instance = VenoInstance::getInstance(BaseComponent::m_processId);
    repaint();
    // draw peak signal
    auto leftChannel = getdBForChannel(instance->audioBuffer->leftPeak);
    selectColourByPeak(leftChannel);
    glBegin(GL_TRIANGLES);
    glVertex2f(-0.9f, leftChannel);
    glVertex2f(-0.9f, -1.0f);
    glVertex2f(-0.08f, -1.0f);
    glEnd();
    auto rightChannel = getdBForChannel(instance->audioBuffer->rightPeak);
    selectColourByPeak(rightChannel);
    glBegin(GL_TRIANGLES);
    glVertex2f(0.9f, rightChannel);
    glVertex2f(0.9f, -1.0f);
    glVertex2f(0.08f, -1.0f);
    glEnd();
}

void Waveforms::paint(Graphics& g)
{
    if (!VenoInstance::hasInstance(m_processId))
    {
        return;
    }
    std::shared_ptr<Theme> theme = Config::getInstance()->getCurrentTheme();
    auto accent = theme->getColour(ThemeColour::lcd);
    g.setColour(accent);
    g.setFont(*VenoFonts::getLCD());
    VeNo::Utils::setFontSize(16.0f, g);
    if (m_isWelcome)
    {
        drawWelcome(g, getWidth(), getHeight(), 0, 0);
        m_ticks++;
        if (m_ticks > m_time_needed_startup)
        {
            m_isWelcome = false;
            m_ticks = 0;
            m_needToClear = true;
        }
    }
    else if (m_isStarting)
    {
        g.drawText(m_warmUpText[m_randomText], 0, 0, getWidth(), getHeight(),
                   Justification::centred, true);
        m_ticks++;
        if (m_ticks > m_time_needed_startup)
        {
            m_isStarting = false;
            m_ticks = 0;
            m_needToClear = true;
        }
    }
    else if (m_isChangingData)
    {
        m_dBScale->m_mode = -1;
        m_dBScale->repaint();
        drawChangedParameter(g, getWidth(), getHeight(), 0, 0);
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
            m_dBScale->repaint();
            g.resetToDefaultState();
            m_needToClear = false;
        }
        g.setFont(*VenoFonts::getLCD());
        VeNo::Utils::setFontSize(16.0f, g);
        if (m_mode == 0)
        {
            auto instance = VenoInstance::getInstance(BaseComponent::m_processId);
            g.setColour(theme->getColour(ThemeColour::lcd_bg));
            float size = VeNo::Utils::setFontSize(7, g);
            auto halfWidth = getWidth() / 2;
            auto halfHalfWidth = halfWidth / 2;
            auto y = getHeight() - size;
            g.drawText(std::to_string(instance->audioBuffer->leftPeak), halfWidth - halfHalfWidth - (size * 1.5), y,
                       (size * 3), size, Justification::centred, false);
            g.drawText(std::to_string(instance->audioBuffer->rightPeak), halfWidth + halfHalfWidth - (size * 1.5), y,
                       (size * 3), size, Justification::centred, false);
        }
    }
}

void Waveforms::drawChangedParameter(Graphics& g, int w, int h, int x, int y) const
{
    int halfHeight = h / 2;
    float font = VeNo::Utils::setFontSize(12, g);
    g.drawText(m_changedParameter, x, y + halfHeight - font, w, font, Justification::centred, true);
    g.drawText(std::to_string(m_changedValue), x, y + halfHeight + 4, w, font, Justification::centred,
               true);
}

void Waveforms::drawWelcome(Graphics& g, int w, int h, int x, int y)
{
    float font = VeNo::Utils::setFontSize(12, g);
    int halfHeight = h / 2;
    g.drawText(m_readyText, x, y + halfHeight - font, w, font, Justification::centred, true);
    g.drawText(SystemStats::getLogonName(), x, y + halfHeight + 4, w, font, Justification::centred,
               true);
}

void Waveforms::drawSpectrum()
{
}

void Waveforms::selectColourByPeak(float value)
{
    auto theme = Config::getInstance()->getCurrentTheme();
    if (theme == nullptr)
    {
        return;
    }
    auto color = theme->getColour(ThemeColour::lcd);
    m_shaderProgram->setUniform("color", color.getFloatRed(), color.getFloatGreen(), color.getFloatBlue(),
                                color.getFloatAlpha());
    if (value > 0.87)
    {
        color = theme->getColour(ThemeColour::clip);
    }
    else if (value > 0.75)
    {
        color = theme->getColour(ThemeColour::warning);
    }
    m_shaderProgram->setUniform("gradientColor", color.getFloatRed(), color.getFloatGreen(), color.getFloatBlue(),
                                color.getFloatAlpha());
}

float Waveforms::getdBForChannel(float value)
{
    return jmap(value, -30.0f, 0.0f, -1.0f,
                0.9f);
}

void Waveforms::setFps()
{
    if (m_currentFps != Config::getInstance()->getFps())
    {
        m_currentFps = Config::getInstance()->getFps();
        // is something that
        m_time_needed = 4000 / m_currentFps;
        m_time_needed_startup = 1000 / m_currentFps;
        startTimer(m_currentFps);
    }
}
void Waveforms::resized()
{
    auto halfWidth = getWidth() / 2;
    auto w = VeNo::Utils::getCalculatedWidth(21);
    m_dBScale->setBounds(halfWidth - (w / 2), 0, w, getHeight());
}

void Waveforms::getState()
{
    if (VenoInstance::hasInstance(m_processId) && VenoInstance::getInstance(m_processId)->state->m_isFirstEditor)
    {
        VenoInstance::getInstance(m_processId)->state->m_isFirstEditor = false;
        m_isWelcome = true;
        m_isStarting = true;
        m_needToClear = true;
    }
}

void Waveforms::parameterChanged(const std::string& parameterID, const std::string& translation, float newValue)
{
    m_changedParameter = translation;
    m_changedValue = newValue;
    m_isChangingData = true;
}
