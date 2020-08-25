#include "ConfigComponent.h"
#include <utility>

ConfigComponent::ConfigComponent (std::string pid)
{
    m_pid = std::move(pid);
    m_colors.resize(8);
    auto theme = Config::getInstance()->getCurrentTheme();
    for (int i = 0; i < 8; i++)
    {
        m_colors[i] = std::make_unique<VeNoColour>(m_pid, getColorForId(i));
        m_colors[i]->setName(m_names[i]);
        addAndMakeVisible(m_colors[i].get());
    }
    m_preColours = std::make_unique<VenoPreColours>(m_pid);
    addAndMakeVisible(*m_preColours);
    flexBox.flexDirection = FlexBox::Direction::row;
    flexBox.justifyContent = FlexBox::JustifyContent::flexStart;
    flexBox.flexWrap = FlexBox::Wrap::wrap;
    auto w = 200;
    auto h = 100;
    for (auto& color : m_colors)
    {
        auto item = FlexItem(w, h, *color);
        item.margin = FlexItem::Margin(5, 5, 5, 5);
        flexBox.items.add(item);
    }
}

ConfigComponent::~ConfigComponent ()
{
    for (auto& color : m_colors)
    {
        color.reset();
    }
    m_colors.clear();
    m_preColours.reset(nullptr);
}

ThemeColour ConfigComponent::getColorForId (int id)
{
    switch (id)
    {
        default:
            return ThemeColour::bg;
        case 1:
            return ThemeColour::bg_two;
        case 2:
            return ThemeColour::accent;
        case 3:
            return ThemeColour::accent_two;
        case 4:
            return ThemeColour::warning;
        case 5:
            return ThemeColour::clip;
        case 6:
            return ThemeColour::lcd_bg;
        case 7:
            return ThemeColour::lcd;
    }
}

void ConfigComponent::paint (Graphics& g)
{
    g.fillAll(Colours::black);
}

void ConfigComponent::resized ()
{
    auto bounds = Rectangle<int>();
    bounds.setBounds(0,0,getWidth(), getHeight()-200);
    flexBox.performLayout(bounds);
    m_preColours->setBounds(0, getHeight() - 200, getWidth(), 200);
}
