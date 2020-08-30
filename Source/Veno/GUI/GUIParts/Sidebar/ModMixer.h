#ifndef VENO_MODMIXER_H
#define VENO_MODMIXER_H


#include "JuceHeader.h"
#include "../../Components/BaseComponent.h"
#include "../../Components/Base/VeNoKnob.h"

class ModMixer : public BaseComponent
{
public:
    explicit ModMixer (const std::string& pid);

    ~ModMixer () override;

    void resized () override;

    void paint (Graphics& g) override;

protected:
    std::vector<std::unique_ptr<VeNoKnob>> m_modKnobs;
};


#endif //VENO_MODMIXER_H
