//
// Created by versustune on 01.03.20.
//

#include "Config.h"

std::shared_ptr<Config> Config::instance = nullptr;

Config::Config() {
    // i want to load the config file here...
    initConfig();

    theme = std::make_shared<Theme>(config);
    theme->init();
}

void Config::saveAll() {
    if (config != nullptr) {
        config->saveIfNeeded();
    }
}

int Config::getCurrentLook() {
    if (currentLook > 1) {
        currentLook = 0;
    }
    return currentLook;
}

void Config::initConfig() {
    PropertiesFile::Options options;
    options.applicationName = "config";
    options.folderName = "veno";
    options.filenameSuffix = "xml";
    config = std::make_unique<PropertiesFile>(options);
}

std::shared_ptr<Theme> Config::getCurrentTheme() {
    return theme;
}

double Config::getScale() {
    return 0;
}

void Config::setColourForIndex(Colour *colour, ThemeColour index) {
    if (theme) {
        theme->setColour(index, colour);
    }
}

Config::~Config() {
    config->save();
    theme.reset();
    config.reset();
}

//LEAK DETECTOR FIX!
void Config::registerEditor(AudioProcessorEditor *editor, const std::string &name) {
    editors[name] = editor;
}

void Config::removeEditor(const std::string &name) {
    editors.erase(name);
    if (editors.empty()) {
        instance = nullptr;
    }
}

//for LCD :P let's be a bit funny xD
int Config::getEditorCount() {
    editors.size();
}
