#ifndef VENO_VENOPARAMETERSTRINGHELPER_H
#define VENO_VENOPARAMETERSTRINGHELPER_H

#include <string>
#include <vector>

/**
 * Index mapper is at Parameter.md!
 */
class VeNoParameterStringHelper
{
private:
    std::vector<std::string> baseStrings;
    std::vector<std::string> oscillatorOne;
    std::vector<std::string> oscillatorTwo;
    std::vector<std::string> oscillatorThree;
    std::vector<std::string> oscillatorFour;
    static std::string osc1;
    static std::string osc2;
    static std::string osc3;
    static std::string osc4;
public:
    static VeNoParameterStringHelper& getInstance ()
    {
        static VeNoParameterStringHelper instance;
        return instance;
    }

    VeNoParameterStringHelper ();

    ~VeNoParameterStringHelper () = default;

    void initOscillatorCaches ();

    void initBaseCaches ();

    static std::string& getForOscillator (std::string& name, int index);

    static std::string& getBase (int index);

    std::vector<std::string>& getRealContainer (int index);
};


#endif //VENO_VENOPARAMETERSTRINGHELPER_H
