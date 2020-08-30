#ifndef VENO_PRESETMANAGER_H
#define VENO_PRESETMANAGER_H

#include <string>

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

protected:
    std::string m_pid;
    std::string m_name;
};

#endif //VENO_PRESETMANAGER_H
