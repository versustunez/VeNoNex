//
// Created by versustune on 01.03.20.
//

#ifndef VENO_CONFIG_H
#define VENO_CONFIG_H

#include "JuceHeader.h"
#include "../GUI/LookAndFeel/LookHandler.h"
#include "../GUI/Theme/Theme.h"
#include <memory>

class Config
{
private:
    std::shared_ptr<PropertiesFile> m_config = nullptr;
    std::shared_ptr<Theme> m_theme = nullptr;
    static std::shared_ptr<Config> m_instance;
    int m_currentLook = 0; //nah move the bitch logic from current to next
    std::unordered_map<std::string, AudioProcessorEditor*> m_editors;
    int m_fps = 60;
public:
    static std::shared_ptr<Config> getInstance ();
    void saveAll ();
    int getCurrentLook ();
    void setColourForIndex (Colour* colour, ThemeColour index);
    std::shared_ptr<Theme> getCurrentTheme ();
    double getScale ();
    // can be public but doesnt need!
    Config ();
    ~Config ();
    void registerEditor (AudioProcessorEditor* editor, const std::string& name);
    void removeEditor (const std::string& name);
    int getEditorCount ();
    int getFps () const;
protected:
    void initConfig ();
};
#endif //VENO_CONFIG_H
