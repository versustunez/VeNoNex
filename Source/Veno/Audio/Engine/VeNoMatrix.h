#ifndef VENO_VENOMATRIX_H
#define VENO_VENOMATRIX_H

#include <string>
#include <unordered_map>
#include <vector>
#include "Modulator.h"
#include "ModulateValue.h"
#include "JuceHeader.h"

// class that modulate everything :D
struct VeNoMatrixTarget
{
    std::string name;
    std::string source;
    float amount = 0; // always 0 to 1 <-- apply amount to modulator
    [[nodiscard]] std::string toString () const;

    static VeNoMatrixTarget* fromString (const std::string& value);
};

//@todo rebuild to new unlimited implementation!
// and make compatible with the value class that is used for saving and sync the ValueTree...
class VeNoMatrix
{
public:
    explicit VeNoMatrix (const std::string& processId);

    ~VeNoMatrix ();

    void updateSlots ();

    void addModulator (const std::string& name, Modulator* modulator);

    void removeModulator (const std::string& name);

    void setMatrixModulation (const std::string& name, const std::string& source, float amount);

    std::unique_ptr<XmlElement> saveMatrixToXML ();

    void getMatrixFromXML (std::unique_ptr<XmlElement>& xml);

private:
    std::unordered_map<std::string, Modulator*> m_modulators; //all sources
    std::unordered_map<std::string, VeNoMatrixTarget*> m_slots;
    std::string m_processId;
protected:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (VeNoMatrix)
};

#endif //VENO_VENOMATRIX_H
