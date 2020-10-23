#include "GuiMatrixItem.h"
#include "../../../VenoInstance.h"

namespace VeNo
{

    GuiMatrixItem::GuiMatrixItem (std::string& pid,std::string key)
            : BaseComponent (pid), m_key (std::move(key))
    {
        auto inst = VenoInstance::getInstance (m_processId);
        auto& slot = inst->matrix->getSlots ()[m_key];
        m_modulator = std::make_unique<juce::Label> ("modulator", inst->matrix->getModulatorNameFromSlot (m_key));
        m_modulation = std::make_unique<juce::Label> ("modulation",
                                                      inst->handler->getParameter (slot->name)->getShowName ());
        m_modulator->setJustificationType(Justification::centred);
        m_modulation->setJustificationType(Justification::centred);
        m_amount = std::make_unique<VeNoKnob> ("unk", m_processId);
        m_amount->m_slider->setRange(0.0, 1.0, 0.05);
        m_amount->m_slider->setValue(slot->amount, NotificationType::dontSendNotification);
        m_amount->m_slider->addListener(this);
        m_btn = std::make_unique<VeNoTextButton> ("unk", "Delete", m_processId);
        m_btn->m_button->addListener(this);
        addAndMakeVisible (*m_modulator);
        addAndMakeVisible (*m_modulation);
        addAndMakeVisible (*m_amount);
        addAndMakeVisible (*m_btn);
    }

    GuiMatrixItem::~GuiMatrixItem ()
    {
        m_modulator.reset (nullptr);
        m_modulation.reset (nullptr);
        m_amount.reset (nullptr);
        m_btn.reset (nullptr);
    }

    void GuiMatrixItem::resized ()
    {
        m_modulator->setBounds(0,0,200,100);
        m_modulation->setBounds(250,0,200,100);
        m_amount->setBounds(600, 15, 70, 85);
        m_btn->setBounds(715, 25, 100, 50);
    }

    void GuiMatrixItem::paint (Graphics& g)
    {
        auto theme = Config::getInstance()->getCurrentTheme();
        g.setColour(theme->getColour(ThemeColour::accent)),
        g.fillRect(0, getHeight()-1, getWidth(), 1);
    }

    void GuiMatrixItem::buttonClicked (Button* button)
    {
        auto inst = VenoInstance::getInstance (m_processId);
        inst->matrix->removeSlot(m_key);
        inst->state->matrix->m_component->m_list->update();
    }

    void GuiMatrixItem::buttonStateChanged (Button* button)
    {
    }

    void GuiMatrixItem::sliderValueChanged (Slider* slider)
    {
        auto inst = VenoInstance::getInstance (m_processId);
        inst->matrix->setMatrixModulationValue(m_key, slider->getValue());
    }

    void GuiMatrixItem::sliderDragStarted (Slider* slider)
    {
    }

    void GuiMatrixItem::sliderDragEnded (Slider* slider)
    {
    }
}