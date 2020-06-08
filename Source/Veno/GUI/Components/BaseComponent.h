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
class BaseComponent : public Component {
private:
    std::string m_group;
    std::string m_name;
    bool m_enableLabel = false;
    std::shared_ptr<LabelComponent> m_label;
    std::shared_ptr<LookHandler> m_lookHandler;
public:
    BaseComponent();
    ~BaseComponent() override;
    void addLabel(const std::string& label, LabelPosition labelPosition);
    void setParameter(std::string name, std::string group);
    void resized() override;
    void paint(Graphics &g) override;
protected:
};


#endif //VENO_BASECOMPONENT_H
