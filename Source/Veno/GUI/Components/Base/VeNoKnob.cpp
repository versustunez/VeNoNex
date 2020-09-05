#include "VeNoKnob.h"
#include "../../Fonts/Fonts.h"
#include "../../../VenoInstance.h"
#include "../../../Utils.h"

VeNoKnob::VeNoKnob (const std::string& name, const std::string& pid)
        : BaseComponent (pid), VeNoComponentListener (pid),
        m_slider(std::make_unique<Slider>())
{
    m_slider->setComponentID (name);
    m_slider->setTextBoxStyle (Slider::NoTextBox, true, 0, 0);
    m_slider->setSliderStyle (Slider::SliderStyle::RotaryVerticalDrag);
    m_slider->setPopupDisplayEnabled (true, true, getParentComponent (), 1000);
    m_slider->setPopupMenuEnabled (true);
    m_slider->addListener (this);
    auto treeState = VenoInstance::getInstance (m_processId)->treeState;
    m_attachment = std::make_unique<SliderAttachment> (*treeState, name, *m_slider);
    addAndMakeVisible (*m_slider);
}

VeNoKnob::~VeNoKnob ()
{
    m_slider->removeListener (this);
    if (m_label != nullptr)
    {
        m_label.reset ();
    }
    m_attachment.reset ();
    m_slider.reset ();
}

void VeNoKnob::init (const std::string& label)
{
    m_labelText = label;
    addLabel (label, LabelPosition::BOTTOM);
    m_label->setEditable (true);
    m_label->setJustification (Justification::centred);
    m_label->setListener (this);
}

void VeNoKnob::resized ()
{
    BaseComponent::resized ();
    auto labelHeight = VeNo::Utils::getCalculatedHeight (15);
    m_slider->setBounds (0, 0, getWidth (), getHeight () - labelHeight);
}

void VeNoKnob::editorShown (Label* label, TextEditor& editor)
{
    char str[20];
    snprintf (str, 20, "%.4f", m_slider->getValue ());
    editor.setFont (*VenoFonts::getNormal ());
    editor.setJustification (Justification::centred);
    editor.setText (str, false);
}

void VeNoKnob::editorHidden (Label* label, TextEditor& editor)
{
    try
    {
        double val = std::stof (label->getText ().toStdString ());
        m_slider->setValue (val);
    } catch (const std::invalid_argument&)
    {
    }
    label->setText (m_labelText, NotificationType::dontSendNotification);
}

void VeNoKnob::labelTextChanged (Label* labelThatHasChanged)
{

}
