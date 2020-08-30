#include "VenoPreColours.h"
#include "../../../Core/Config.h"
#include "../../../VenoInstance.h"

VenoPreColours::VenoPreColours (const std::string& processId) : BaseComponent (processId)
{
    initSliders ();
    initButtons ();
}

VenoPreColours::~VenoPreColours ()
{
    m_scaleSlider.reset ();
    for (int i = 0; i < 4; ++i)
    {
        m_pre[i].reset ();
    }
}

void VenoPreColours::initSliders ()
{
    m_scaleSliderLabel = std::make_shared<Label> ();
    m_scaleSliderLabel->setText ("Scale", NotificationType::dontSendNotification);
    m_scaleSlider = std::make_shared<Slider> ();
    m_scaleSlider->setRange (0.5f, 2.5f, 0.1);
    m_scaleSlider->setValue (Config::getInstance ()->getScale ());
    m_scaleSlider->setSliderStyle (Slider::SliderStyle::LinearHorizontal);
    m_scaleSlider->setTooltip ("Scale");
    m_scaleSlider->addListener (this);
    addAndMakeVisible (*m_scaleSlider);
    addAndMakeVisible (*m_scaleSliderLabel);
}

void VenoPreColours::sliderValueChanged (Slider* slider)
{
    if (slider == m_scaleSlider.get ())
    {
        Config::getInstance ()->setScale (slider->getValue ());
    }
}

void VenoPreColours::initButtons ()
{
    //4
    m_pre.resize (5);
    for (int i = 0; i < 5; ++i)
    {
        m_pre[i] = std::make_unique<TextButton> (m_names[i]);
        m_pre[i]->addListener (this);
        m_pre[i]->setMouseCursor (MouseCursor::PointingHandCursor);
        addAndMakeVisible (m_pre[i].get ());
    }
}

void VenoPreColours::buttonClicked (Button* button)
{
    auto text = button->getButtonText ().toStdString ();
    Config::getInstance ()->getCurrentTheme ()->setDefault (text);
    if (VenoInstance::getInstance (m_processId)->state->configScreen != nullptr)
    {
        VenoInstance::getInstance (m_processId)->state->configScreen->repaint ();
    }
}

void VenoPreColours::resized ()
{
    auto bounds = Rectangle<int> ();
    bounds.setBounds (0, 0, getWidth (), getHeight () - 100);
    auto bWidth = (getWidth () - 80) / 5;
    for (int i = 0; i < 5; ++i)
    {
        m_pre[i]->setBounds ((bWidth * i) + 40, 110, bWidth, 50);
    }
    // set slider and button positio
    m_scaleSlider->setBounds (20, 50, getWidth () - 40, 50);
    m_scaleSliderLabel->setBounds (20, 30, 40, 20);
}
