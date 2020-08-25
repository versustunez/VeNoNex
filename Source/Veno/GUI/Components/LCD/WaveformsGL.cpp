/**
 * @fixme use Modern GL to shrink transfer times
 */

#include "Waveforms.h"
#include <utility>
#include "../../../Core/Config.h"
#include "../../../Utils.h"
#include "../../../VenoInstance.h"

#ifdef __APPLE__
#include <GLFW/glfw3.h>
#endif


void Waveforms::newOpenGLContextCreated ()
{
    compileOpenGLShaderProgram ();
    m_context.extensions.glGenBuffers (1, &vbo);
}

void Waveforms::openGLContextClosing ()
{

}

void Waveforms::renderOpenGL ()
{
    if (!VenoInstance::hasInstance (m_processId) || !m_context.isActive () || !m_context.isAttached () ||
        m_shaderProgram == nullptr || !m_shaderProgram->getLastError ().isEmpty ())
    {
        stopTimer ();
        return;
    }

    if (!isShowing ())
    {
        return;
    }

    auto theme = Config::getInstance ()->getCurrentTheme ();
    if (theme == nullptr)
    {
        return;
    }
    OpenGLHelpers::clear (theme->getColour (ThemeColour::lcd_bg));
    //glViewport(0, 0, getWidth(), getHeight());
    glEnable (GL_BLEND);
    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    m_shaderProgram->use ();
    auto color = theme->getColour (ThemeColour::lcd);
    m_shaderProgram->setUniform ("color", color.getFloatRed (), color.getFloatGreen (), color.getFloatBlue (),
                                 color.getFloatAlpha ());
    // same color currently! will set to a diff if peak is detected!
    m_shaderProgram->setUniform ("gradientColor", color.getFloatRed (), color.getFloatGreen (), color.getFloatBlue (),
                                 color.getFloatAlpha ());
    if (m_isStarting || m_isChangingData)
    {
        return;
    }
    switch (m_mode)
    {
        case 1:
            drawAudioOutput ();
            break;
        case 2:
            drawSpectrum ();
            break;
        case 3:
            drawWaveTable ();
            break;
        case 4:
            break;
        default:
            drawPeakMeter ();
    }
}

void Waveforms::compileOpenGLShaderProgram ()
{
    std::unique_ptr<OpenGLShaderProgram> shaderProgramAttempt
            = std::make_unique<OpenGLShaderProgram> (m_context);
    if (shaderProgramAttempt->addVertexShader ({BinaryData::WaveForm_vertex_glsl})
        && shaderProgramAttempt->addFragmentShader ({BinaryData::WaveForm_fragment_glsl})
        && shaderProgramAttempt->link ())
    {
        m_shaderProgram = std::move (shaderProgramAttempt);
    }
    else
    {
        DBG(shaderProgramAttempt->getLastError ().toStdString ());
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
    for (float j : buffer)
    {
        try
        {
            glVertex2f (posX, j);
            posX += inc;
        } catch (std::exception& e)
        {
            DBG(e.what ());
            //something is wrong skip the draw and end it!
            break;
        }
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
    repaint ();
    // draw peak signal
    auto leftChannel = VeNo::Utils::dBForChannel (instance->audioBuffer->leftPeak);
    auto rightChannel = VeNo::Utils::dBForChannel (instance->audioBuffer->rightPeak);
    auto maxValue = VeNo::Utils::getHigherValue (leftChannel, rightChannel);
    selectColourByPeak (maxValue);
    m_vertexBuffer.resize (6);
    m_vertexBuffer = {
            {-0.9f,  leftChannel},
            {-0.9f,  -1.0f},
            {-0.08f, -1.0f},
            {0.9f,   rightChannel},
            {0.9f,   -1.0f},
            {0.08f,  -1.0f}
    };
    m_context.extensions.glBindBuffer (GL_ARRAY_BUFFER, vbo);
    m_context.extensions.glBufferData (GL_ARRAY_BUFFER, sizeof (VeNo::GL::Vertex2) * m_vertexBuffer.size (),
                                       m_vertexBuffer.data (), GL_DYNAMIC_DRAW);
    m_context.extensions.glVertexAttribPointer (0, 2, GL_FLOAT, GL_FALSE, sizeof (VeNo::GL::Vertex2), nullptr);
    m_context.extensions.glEnableVertexAttribArray (0);
    glDrawArrays (
            GL_TRIANGLES,
            0,
            m_vertexBuffer.size ()
    );
    m_context.extensions.glDisableVertexAttribArray (0);

}

void Waveforms::drawSpectrum ()
{
    auto buffer = m_fft->scopeData;
    int size = m_fft->scopeSize;
    glBegin (GL_LINE_LOOP);
    float posX = -1;
    float inc = 2.0f / (float) size;
    glVertex2f (posX, -1);
    for (int i = 0; i < size; i++)
    {
        glVertex2f (posX, buffer[i]);
        posX += inc;
    }
    glVertex2f (posX, -1);
    glEnd ();
}

void Waveforms::selectColourByPeak (float value)
{
    auto theme = Config::getInstance ()->getCurrentTheme ();
    if (theme == nullptr)
    {
        return;
    }
    auto color = theme->getColour (ThemeColour::lcd);
    m_shaderProgram->setUniform ("color", color.getFloatRed (), color.getFloatGreen (), color.getFloatBlue (),
                                 color.getFloatAlpha ());
    if (value > 0.87)
    {
        color = theme->getColour (ThemeColour::clip);
    }
    else if (value > 0.75)
    {
        color = theme->getColour (ThemeColour::warning);
    }
    m_shaderProgram->setUniform ("gradientColor", color.getFloatRed (), color.getFloatGreen (), color.getFloatBlue (),
                                 color.getFloatAlpha ());
}
