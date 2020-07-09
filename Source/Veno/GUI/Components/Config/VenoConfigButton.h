//
// Created by versustune on 14.06.20.
//

#ifndef VENO_VENOCONFIGBUTTON_H
#define VENO_VENOCONFIGBUTTON_H

#include "JuceHeader.h"
#include "../BaseComponent.h"

class VenoConfigButton : public BaseComponent
{
public:
    VenoConfigButton (const std::string& processId);
    ~VenoConfigButton() = default;
    void paint (Graphics& g) override;
    void mouseDown (const MouseEvent& event) override;
private:

};
#endif //VENO_VENOCONFIGBUTTON_H