//
// Created by versustune on 11.06.20.
//

#ifndef VENO_WAVEFORMS_H
#define VENO_WAVEFORMS_H

#include "JuceHeader.h"
#include "../BaseComponent.h"

#define RANDOM_TEXT_COUNT 5
// opengl context :D
class Waveforms : public BaseComponent,
                  private OpenGLRenderer,
                  private AsyncUpdater,
                  private Timer
{
protected:
    bool m_enableModeToggle = true;
    int m_mode = 0;
    std::string m_readyText = "=WELCOME=";
    std::string m_warmUpText[RANDOM_TEXT_COUNT] = {"Warmup...", "Mayonnaise", "Dont shake the baby", "Awesome stuff",
                                                   "drink beer"};
    int pickRandomText = 0;
    bool m_isWelcome = true;
    bool m_isStarting = true;
    int m_ticks = 0;
    int m_time_needed_startup = 0;
    int m_time_needed = 0;
    bool needToClear = false;
public:
    explicit Waveforms (const std::string& processId);
    ~Waveforms () override;
    void newOpenGLContextCreated () override;
    void openGLContextClosing () override;
    void renderOpenGL () override;
    void handleAsyncUpdate () override;
    void mouseDown (const MouseEvent& e) override;
    void mouseDrag (const MouseEvent& e) override;
    void paint (Graphics& g) override;
    bool m_isChangingData = false;
    std::string changingParameter = "";
    float changedValue = 0;
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
    OpenGLContext m_context;
    std::unique_ptr<OpenGLShaderProgram> shaderProgram;
};
#endif //VENO_WAVEFORMS_H