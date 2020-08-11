//
// Created by versustune on 14.06.20.
//

#include "VenoPreColours.h"
#include "../../../Core/Config.h"

VenoPreColours::VenoPreColours (const std::string& processId) : BaseComponent(processId)
{
    initSliders();
    initButtons();
}

VenoPreColours::~VenoPreColours ()
{
    m_scaleSlider.reset();
    m_fpsSlider.reset();
    for (int i = 0; i < 4; ++i)
    {
        m_pre[i].reset();
    }
}

void VenoPreColours::initSliders ()
{
    m_fpsSlider = std::make_shared<Slider>();
    m_fpsSlider->setRange(15, 90, 1);
    m_fpsSlider->setValue(Config::getInstance()->getFps());
    m_fpsSlider->setSliderStyle(Slider::SliderStyle::LinearHorizontal);
    m_fpsSlider->setTooltip("FPS");
    m_scaleSlider = std::make_shared<Slider>();
    m_scaleSlider->setRange(0.5f, 2.5f, 0.1);
    m_scaleSlider->setValue(Config::getInstance()->getScale());
    m_scaleSlider->setSliderStyle(Slider::SliderStyle::LinearHorizontal);
    m_scaleSlider->setTooltip("Scale");
    m_scaleSlider->addListener(this);
    m_fpsSlider->addListener(this);
    addAndMakeVisible(*m_fpsSlider);
    addAndMakeVisible(*m_scaleSlider);
}

void VenoPreColours::sliderValueChanged (Slider* slider)
{
    if (slider == m_fpsSlider.get())
    {
        Config::getInstance()->setFps(slider->getValue());
    }
    if (slider == m_scaleSlider.get())
    {
        Config::getInstance()->setScale(slider->getValue());
    }
}

void VenoPreColours::initButtons ()
{
    //4
    m_pre.resize(4);
    for (int i = 0; i < 4; ++i)
    {
        m_pre[i] = std::make_unique<TextButton>(m_names[i]);
        m_pre[i]->addListener(this);
        addAndMakeVisible(m_pre[i].get());
    }
}

void VenoPreColours::buttonClicked (Button* button)
{
    auto text = button->getButtonText().toStdString();
    Config::getInstance()->getCurrentTheme()->setDefault(text);
}

void VenoPreColours::resized ()
{
    auto bounds = Rectangle<int>();
    bounds.setBounds(0,0,getWidth(), getHeight()-100);
    auto bWidth = (getWidth()-80) / 4;
    for (int i = 0; i < 4 ; ++i)
    {
        m_pre[i]->setBounds((bWidth * i) + 40, 110, bWidth, 50);
    }
    // set slider and button position
    m_fpsSlider->setBounds(20, 0, getWidth()-40, 50);
    m_scaleSlider->setBounds(20, 50, getWidth()-40, 50);
}
