//
// Created by versustune on 09.06.20.
//

#ifndef VENO_SYNTHINSTANCE_H
#define VENO_SYNTHINSTANCE_H


#include <string>

// class that hold all voices, oscillators and other stuff :)
class SynthInstance {
private:
    std::string m_processId;
public:
    explicit SynthInstance(std::string processId);
    ~SynthInstance() = default;
protected:
};


#endif //VENO_SYNTHINSTANCE_H
