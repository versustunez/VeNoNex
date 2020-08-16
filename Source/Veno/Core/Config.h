//
// Created by versustune on 01.03.20.
//

#ifndef VENO_CONFIG_H
#define VENO_CONFIG_H

#include "JuceHeader.h"
#include "../GUI/LookAndFeel/LookHandler.h"
#include "../GUI/Theme/Theme.h"
#include <memory>
#include <unordered_map>

class Config : public Timer
{
private:
    std::shared_ptr<PropertiesFile> m_config = nullptr;
    std::shared_ptr<Theme> m_theme = nullptr;
    static std::shared_ptr<Config> m_instance;
    int m_currentLook = 0; //nah move the bitch logic from current to next
    std::unordered_map<std::string, AudioProcessorEditor*> m_editors;
    std::shared_ptr<LookHandler> m_lookHandler;
public:
    int m_fps = 60;
    float m_scale = 1.0f;
    static std::shared_ptr<Config> getInstance ();
    static bool hasInstance();
    void saveAll ();
    int getCurrentLook ();
    void setColourForIndex (Colour* colour, ThemeColour index);
    std::shared_ptr<Theme> getCurrentTheme ();
    double getScale () const;
    // can be public but doesnt need!
    Config ();
    ~Config ();
    void registerEditor (AudioProcessorEditor* editor, const std::string& name);
    void removeEditor (const std::string& name);
    int getEditorCount ();
    int getFps () const;
    void setScale(float value);
    void setFps(float value);
    void timerCallback () override;
    void repaintAll();
protected:
    void initConfig ();
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Config);
};
#endif //VENO_CONFIG_H
