#include "VeNoKeyboard.h"
#include "../../VenoInstance.h"

VeNoKeyboard::VeNoKeyboard (const std::string& id) : BaseComponent (id)
{
    keyboardComponent = std::make_unique<MidiKeyboardComponent>(keyboardState, MidiKeyboardComponent::horizontalKeyboard);
    keyboardState.addListener(this);
    keyboardComponent->setMidiChannelsToDisplay (0);
    keyboardComponent->setKeyWidth (27);
    keyboardComponent->setAvailableRange (57, 93);
    addAndMakeVisible(*keyboardComponent);
}

VeNoKeyboard::~VeNoKeyboard ()
{
    keyboardComponent.reset(nullptr);
}

void VeNoKeyboard::resized ()
{
    if (keyboardComponent != nullptr) {
        keyboardComponent->setKeyWidth(std::floor(getWidth() / 22));
        keyboardComponent->setBounds(0, 0, getWidth(), getHeight());
    }
}

void VeNoKeyboard::paint (Graphics& g)
{
    BaseComponent::paint (g);
}

void VeNoKeyboard::handleNoteOn (MidiKeyboardState* source, int midiChannel, int midiNoteNumber, float velocity)
{
    VenoInstance::getInstance (m_processId)->getSynthInstance ()->noteOn (midiChannel, midiNoteNumber, velocity);
}

void VeNoKeyboard::handleNoteOff (MidiKeyboardState* source, int midiChannel, int midiNoteNumber, float velocity)
{
    VenoInstance::getInstance (m_processId)->getSynthInstance ()->noteOff (midiChannel, midiNoteNumber, velocity);
}
