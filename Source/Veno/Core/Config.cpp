//
// Created by versustune on 01.03.20.
//

#include "Config.h"
#include "../Fonts/Fonts.h"
#include "../GUI/GUIParts/Sidebar/VenoLogo.h"
#include "../Utils.h"

std::shared_ptr<Config> Config::m_instance = nullptr;

Config::Config ()
{
    // i want to load the m_config file here...
    initConfig();
    m_theme = std::make_shared<Theme>(m_config);
    m_theme->init();
    m_fps = m_config->getIntValue("waveform_fps", 60);
    startTimer(5000);
}

void Config::saveAll ()
{
    if (m_config != nullptr)
    {
        m_config->saveIfNeeded();
    }
}

int Config::getCurrentLook ()
{
    if (m_currentLook > 1)
    {
        m_currentLook = 0;
    }
    return m_currentLook;
}

void Config::initConfig ()
{
    PropertiesFile::Options options;
    options.applicationName = "config";
    options.folderName = "veno";
    options.filenameSuffix = "xml";
    m_config = std::make_unique<PropertiesFile>(options);
    m_scale = (float) m_config->getDoubleValue("scale", 1.0);
}

std::shared_ptr<Theme> Config::getCurrentTheme ()
{
    return m_theme;
}

double Config::getScale () const
{
    return m_scale;
}

void Config::setColourForIndex (Colour* colour, ThemeColour index)
{
    if (m_theme)
    {
        m_theme->setColour(index, colour);
    }
}

Config::~Config ()
{
    m_config->save();
    m_config->setNeedsToBeSaved(false);
    m_theme.reset();
    m_config.reset();
    m_lookHandler.reset();
    stopTimer();
    VenoFonts::destroyAll();
    VenoLogo::deleteInstance();
}

//LEAK DETECTOR FIX!
void Config::registerEditor (AudioProcessorEditor* editor, const std::string& name)
{
    m_editors[name] = editor;
}

void Config::removeEditor (const std::string& name)
{
    m_editors.erase(name);
    if (m_editors.empty())
    {
        m_instance.reset();
        m_theme.reset();
        m_theme = nullptr;
        m_instance = nullptr;
    }
}

//for LCD :P let's be a bit funny xD
int Config::getEditorCount ()
{
    return m_editors.size();
}

std::shared_ptr<Config> Config::getInstance ()
{
    if (m_instance == nullptr)
        m_instance = std::make_shared<Config>();
    return m_instance;
}

int Config::getFps () const
{
    return m_fps;
}

void Config::setScale (float value)
{
    value = VeNo::Utils::clamp(value, 0.5f, 2.5f);
    m_scale = value;
    m_config->setValue("scale", m_scale);
    m_config->setNeedsToBeSaved(true);
    for (auto& editor : m_editors)
    {
        editor.second->setSize(1200 * m_scale, 700 * m_scale);
    }
}

void Config::timerCallback ()
{
    m_config->saveIfNeeded();
}

void Config::repaintAll ()
{
    for (auto& editor : m_editors)
    {
        if (editor.second->isShowing())
        {
            editor.second->repaint();
        }
    }
}

void Config::setFps (float value)
{
    m_fps = (int) VeNo::Utils::clamp(value, 15.0f, 90.0f);
    m_config->setValue("waveform_fps", m_fps);
    m_config->setNeedsToBeSaved(true);
}

bool Config::hasInstance ()
{
    return m_instance != nullptr;
}
