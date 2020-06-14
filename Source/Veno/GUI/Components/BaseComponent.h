//
// Created by versustune on 17.03.20.
//

#ifndef VENO_BASECOMPONENT_H
#define VENO_BASECOMPONENT_H

#include "JuceHeader.h"
#include "LabelComponent.h"
#include "../LookAndFeel/LookHandler.h"
#include <string>

/**
 * this is the base Component of all VeNo Components... it has all important Methods
 */
class BaseComponent : public Component
{
private:
    std::string m_group;
    std::string m_name;
    bool m_enableLabel = false;
public:
    explicit BaseComponent (const std::string& processId);
    ~BaseComponent () override;
    void addLabel (const std::string& label, LabelPosition labelPosition);
    void setParameter (std::string name, std::string group);
    void resized () override;
    void paint (Graphics& g) override;
protected:
    std::string m_processId;
    std::shared_ptr<LabelComponent> m_label;
};
#endif //VENO_BASECOMPONENT_H
