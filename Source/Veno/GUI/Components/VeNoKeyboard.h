#ifndef VENO_VENOKEYBOARD_H
#define VENO_VENOKEYBOARD_H


#include "BaseComponent.h"

class VeNoKeyboard : public BaseComponent, MidiKeyboardComponent::Listener
{
private:
    MidiKeyboardState keyboardState = {};
    std::unique_ptr<MidiKeyboardComponent> keyboardComponent;
public:
    explicit VeNoKeyboard (const std::string& id);

    ~VeNoKeyboard () override;

    void resized () override;

    void paint (Graphics& g) override;

private:
    void handleNoteOn (MidiKeyboardState* source, int midiChannel, int midiNoteNumber, float velocity) override;

    void handleNoteOff (MidiKeyboardState* source, int midiChannel, int midiNoteNumber, float velocity) override;
};


#endif //VENO_VENOKEYBOARD_H
