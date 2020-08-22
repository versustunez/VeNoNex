#ifndef VENO_VENOCHANGELISTENER_H
#define VENO_VENOCHANGELISTENER_H

#include <string>
#include <unordered_map>
#include "VeNoListener.h"

class VeNoChangeListener
{
public:
    VeNoChangeListener() = default;
    ~VeNoChangeListener() = default;
    void addListener(const std::string& name, VeNoListener* listener);
    void removeListener(const std::string& name);
    void notifyListener(const std::string& name, float value);
private:
    std::unordered_map<std::string, VeNoListener*> m_listener;
protected:
    bool hasListener(const std::string& name);
};


#endif //VENO_VENOCHANGELISTENER_H
