#ifndef VENO_WAVEFORMS_H
#define VENO_WAVEFORMS_H

#include "JuceHeader.h"
#include "../BaseComponent.h"
#include "DecibelScale.h"
#include "../../../Core/VeNoListener.h"
#include "../../../Services/FFT.h"
#include "../../GL/VertexStructs.h"

#define RANDOM_TEXT_COUNT 6
#define MODE_COUNT 4

class Waveforms : public BaseComponent,
                  public VeNoListener,
                  private Timer,
                  private AsyncUpdater
{
protected:
    bool m_enableModeToggle = true;
    int m_mode = 0;
    std::string m_warmUpText[RANDOM_TEXT_COUNT] = {"Warmup...", "Mayonnaise", "Dont shake the baby", "Awesome stuff",
                                                   "drink beer", "VeNo N3x"};
    int m_randomText = 0;
    bool m_isStarting = false;
    bool m_needToClear = false;
    int m_ticks = 0;
    int m_time_needed = 20;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Waveforms);
public:
    explicit Waveforms (const std::string& processId);

    ~Waveforms () override;

    void newOpenGLContextCreated ();

    void renderOpenGL ();

    void mouseDown (const MouseEvent& e) override;

    void mouseDrag (const MouseEvent& e) override;

    void paint (Graphics& g) override;

    void resized () override;

    bool m_isChangingData = false;
    std::string m_changedParameter;
    double m_changedValue = 0;

    void parameterChanged (VeNoParameter* parameter) override;

    void notify (const std::string& name, double value) override;

private:
    void handleAsyncUpdate () override;

    void timerCallback () override;

    void drawWaveTable ();

    void drawAudioOutput ();

    void drawSpectrum ();

    void drawPeakMeter (); //?!
    void drawChangedParameter (Graphics& g, int w, int h, int x, int y) const;

    void compileOpenGLShaderProgram ();

    void selectColourByPeak (double value);

    void getState ();

    OpenGLContext* m_context;
    std::unique_ptr<OpenGLShaderProgram> m_shaderProgram;
    std::unique_ptr<DecibelScale> m_dBScale;
    std::unique_ptr<FFT> m_fft;
    double m_previous_value = 0;
    float m_x = 0;
    float m_y = 0;

    // gl
    unsigned int vbo;
    std::vector<VeNo::GL::Vertex2> m_vertexBuffer;
};

#endif //VENO_WAVEFORMS_H
