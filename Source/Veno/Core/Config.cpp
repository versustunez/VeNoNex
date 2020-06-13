//
// Created by versustune on 01.03.20.
//

#include "Config.h"

std::shared_ptr<Config> Config::m_instance = nullptr;

Config::Config() {
    // i want to load the m_config file here...
    initConfig();

    m_theme = std::make_shared<Theme>(m_config);
    m_theme->init();
    m_fps = m_config->getIntValue("waveform_fps", 60);
}

void Config::saveAll() {
    if (m_config != nullptr) {
        m_config->saveIfNeeded();
    }
}

int Config::getCurrentLook() {
    if (m_currentLook > 1) {
        m_currentLook = 0;
    }
    return m_currentLook;
}

void Config::initConfig() {
    PropertiesFile::Options options;
    options.applicationName = "config";
    options.folderName = "veno";
    options.filenameSuffix = "xml";
    m_config = std::make_unique<PropertiesFile>(options);
}

std::shared_ptr<Theme> Config::getCurrentTheme() {
    return m_theme;
}

double Config::getScale() {
    return 1;
}

void Config::setColourForIndex(Colour *colour, ThemeColour index) {
    if (m_theme) {
        m_theme->setColour(index, colour);
    }
}

Config::~Config() {
    m_config->save();
    m_theme.reset();
    m_config.reset();
}

//LEAK DETECTOR FIX!
void Config::registerEditor(AudioProcessorEditor *editor, const std::string &name) {
    m_editors[name] = editor;
}

void Config::removeEditor(const std::string &name) {
    m_editors.erase(name);
    if (m_editors.empty()) {
        m_instance = nullptr;
    }
}

//for LCD :P let's be a bit funny xD
int Config::getEditorCount() {
    return m_editors.size();
}

std::shared_ptr<Config> Config::getInstance() {
    if (m_instance == nullptr)
        m_instance = std::make_shared<Config>();
    return m_instance;
}

int Config::getFps() const {
    return m_fps;
}
