    //
// Created by versustune on 11.06.20.
//

#ifndef VENO_WAVEFORMS_H
#define VENO_WAVEFORMS_H

#include "JuceHeader.h"
#include "../BaseComponent.h"
#include "DecibelScale.h"
#include "../../../Core/VeNoListener.h"

#define RANDOM_TEXT_COUNT 6

class Waveforms : public BaseComponent,
                  public VeNoListener,
                  private OpenGLRenderer,
                  private Timer
{
protected:
    bool m_enableModeToggle = true;
    int m_mode = 0;
    std::string m_readyText = "=WELCOME=";
    std::string m_warmUpText[RANDOM_TEXT_COUNT] = {"Warmup...", "Mayonnaise", "Dont shake the baby", "Awesome stuff",
                                                   "drink beer", "VeNo N3x"};
    int m_randomText = 0;
    bool m_isWelcome = false;
    bool m_isStarting = false;
    int m_ticks = 0;
    int m_time_needed_startup = 0;
    int m_time_needed = 0;
    bool m_needToClear = false;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Waveforms);
public:
    explicit Waveforms (const std::string& processId);
    ~Waveforms () override;
    void newOpenGLContextCreated () override;
    void openGLContextClosing () override;
    void renderOpenGL () override;
    void mouseDown (const MouseEvent& e) override;
    void mouseDrag (const MouseEvent& e) override;
    void paint (Graphics& g) override;
    void resized () override;
    bool m_isChangingData = false;
    std::string m_changedParameter;
    float m_changedValue = 0;
    void parameterChanged(const std::string& parameterID, const std::string& translation, float newValue) override;
private:
    void timerCallback () override;
    void drawWaveTable ();
    void drawAudioOutput ();
    void drawSpectrum ();
    void drawPeakMeter (); //?!
    void drawChangedParameter (Graphics& g, int w, int h, int x, int y) const;
    void drawWelcome (Graphics& g, int w, int h, int x, int y);
    void compileOpenGLShaderProgram ();
    void selectColourByPeak (float value);
    float getdBForChannel (float value);
    void setFps();
    void getState();
    OpenGLContext m_context;
    std::unique_ptr<OpenGLShaderProgram> m_shaderProgram;
    std::unique_ptr<DecibelScale> m_dBScale;
    int m_currentFps = 0;
};
#endif //VENO_WAVEFORMS_H
