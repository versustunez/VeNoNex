#ifndef VENO_PRESETMANAGER_H
#define VENO_PRESETMANAGER_H

#include <string>
#include <memory>
#include "JuceHeader.h"

class PresetManager
{
public:
    explicit PresetManager (const std::string& pid);

    ~PresetManager ();

    void save ();

    void load ();

    void setName (const std::string& name);

    void loadNext ();

    void loadPrev ();

    void toInit ();

    std::unique_ptr<XmlElement> getCurrentData ();

    void setCurrentData (const std::unique_ptr<XmlElement>& data);

    std::string m_name = "Init";

protected:
    std::string m_pid;
};

#endif //VENO_PRESETMANAGER_H
