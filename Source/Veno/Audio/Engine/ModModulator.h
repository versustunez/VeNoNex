#ifndef VENO_MODMODULATOR_H
#define VENO_MODMODULATOR_H


#include <string>
#include "Modulator.h"
#include "VeNoParameter.h"

class ModModulator : public Modulator
{
private:
public:
    ModModulator (std::string name, const std::string& showName, std::string pid);

    ~ModModulator () override;

    float getValue () override;

    void update () override;

protected:
    std::string m_pid;
    std::string m_name;
    VeNoParameter* m_mod{};
};


#endif //VENO_MODMODULATOR_H
