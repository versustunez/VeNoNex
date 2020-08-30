#ifndef VENO_PRESETMANAGERCOMPONENT_H
#define VENO_PRESETMANAGERCOMPONENT_H


#include "../../Components/BaseComponent.h"
#include "../../Components/Presets/PresetAction.h"
#include "../../Components/Presets/PresetEditor.h"

class PresetManagerComponent : public BaseComponent
{
public:
    explicit PresetManagerComponent (const std::string& pid);

    ~PresetManagerComponent () override = default;

    void resized () override;

    void paint (Graphics& g) override;

protected:
    std::unique_ptr<PresetAction> m_prev;
    std::unique_ptr<PresetAction> m_next;
    std::unique_ptr<PresetAction> m_save;
    std::unique_ptr<PresetEditor> m_editor;
};


#endif //VENO_PRESETMANAGERCOMPONENT_H
