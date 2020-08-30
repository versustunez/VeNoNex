#ifndef VENO_PRESETACTION_H
#define VENO_PRESETACTION_H


#include "../BaseComponent.h"

class PresetAction : public BaseComponent
{
public:
    enum Type
    {
        PREV = 0,
        NEXT,
        SAVE
    };

    PresetAction (const std::string& processId, std::string name, Type type);

    ~PresetAction () override;

    void resized () override;

    void paint (Graphics& g) override;

protected:
    std::string m_name;
    Type m_type;
};


#endif //VENO_PRESETACTION_H
