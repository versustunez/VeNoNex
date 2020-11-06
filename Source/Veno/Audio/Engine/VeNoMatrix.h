#ifndef VENO_VENOMATRIX_H
#define VENO_VENOMATRIX_H

#include <string>
#include <unordered_map>
#include <vector>
#include "Modulator.h"
#include "ModulateValue.h"
#include "JuceHeader.h"
#include "../../../vendor/tsl/robin_map.h"

// class that modulate everything :D

struct VeNoMatrixSource
{
    std::string name;
    std::string showName;
    std::vector<Modulator*> sources = {};
};

struct VeNoMatrixTarget
{
    std::string name;
    std::string source;
    double amount = 0;
    std::vector<ModulateValue*> value = {};
    VeNoMatrixSource* modulator;
};

class VeNoMatrix
{
public:
    explicit VeNoMatrix (const std::string& processId);

    ~VeNoMatrix ();

    void updateSlots ();

    void addModulator (const std::string& name, Modulator* modulator);

    void removeModulator (const std::string& name);

    bool setMatrixModulation (const std::string& name, const std::string& source, double amount);

    void setMatrixModulationValue(const std::string& key, double amount);

    XmlElement* saveMatrixToXML ();

    void getMatrixFromXML (XmlElement* xml);

    const tsl::robin_map<std::string, VeNoMatrixSource*>& getModulators();

    tsl::robin_map<std::string, VeNoMatrixTarget*>& getSlots ();

    std::string getModulatorNameFromSlot (const std::string& key);

    void removeSlot (const std::string& key);

    std::vector<VeNoMatrixSource*> m_rawOrder;
    std::vector<ModulateValue*> m_rawMods;

    void addModValue (const std::string& name, ModulateValue* value);

    void clear();

private:
    tsl::robin_map<std::string, VeNoMatrixSource*> m_modulators; //all sources
    tsl::robin_map<std::string, VeNoMatrixTarget*> m_slots;
    tsl::robin_map<std::string, ModulateValue*> m_values;
    std::string m_processId;
    mutable std::mutex _mtx;
protected:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (VeNoMatrix)
};

#endif //VENO_VENOMATRIX_H
