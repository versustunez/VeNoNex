//
// Created by versustune on 13.06.20.
//

#ifndef VENO_VENOMATRIX_H
#define VENO_VENOMATRIX_H

#include <string>
#include <unordered_map>
#include <vector>
#include "Modulator.h"
#include "ModulateValue.h"

// class that modulate everything :D
struct VenoMatrixTarget
{
    std::string name;
    float amount = 0; // always 0 to 1 <-- apply amount to modulator
};
struct VenoMatrixSlot
{
    std::string sourceName;
    VenoMatrixTarget targets[8];
};
class VenoMatrix
{
public:
    explicit VenoMatrix (const std::string& processId);
    ~VenoMatrix ();
    void updateSlots ();
    void addModulator (const std::string& name, Modulator* modulator);
    void addModulateValue (const std::string& name, ModulateValue* modulateValue);
    void removeModulator (const std::string& name);
    void removeModulateValue (const std::string& name);
    VenoMatrixSlot* getSlotById (int id);
private:
    std::unordered_map<std::string, Modulator*> m_modulators; //all sources
    std::unordered_map<std::string, ModulateValue*> m_modulationValues;
    VenoMatrixSlot* m_slots[8]{}; // 8 source slots
    std::string m_processId;
};
#endif //VENO_VENOMATRIX_H
