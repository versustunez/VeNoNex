#include "VeNoSelect.h"
#include "../../../Utils/ComboBoxSetupHelper.h"
#include "../../../VenoInstance.h"
#include "../../../Utils.h"

VeNoSelect::VeNoSelect (const std::string& name, const std::string& pid)
        : BaseComponent (pid),
          m_select (std::make_unique<juce::ComboBox> ())
{
    m_select->setComponentID (name);
    addAndMakeVisible (*m_select);
    auto treeState = VenoInstance::getInstance (m_processId)->treeState;
    m_attachment = std::make_unique<ComboBoxAttachment> (*treeState, name, *m_select);
    addAndMakeVisible (*m_select);
}

VeNoSelect::~VeNoSelect ()
{
    m_attachment.reset (nullptr);
    m_select.reset ();
    if (m_label != nullptr)
    {
        m_label.reset();
    }
}

void VeNoSelect::addItem (const std::string& item)
{
    m_select->addItem (item, m_lastAddItem);
    m_lastAddItem++;
}

void VeNoSelect::select (int i)
{
    m_select->setSelectedId (i, NotificationType::dontSendNotification);
}

void VeNoSelect::init (const std::string& label, LabelPosition position, VeNoSelect::Type type)
{
    BaseComponent::addLabel (label, position);
    BaseComponent::m_label->setJustification (Justification::centred);
    ComboBoxSetupHelper::setup (*this, type);
}

void VeNoSelect::resized ()
{
    if (m_label != nullptr)
    {
        LabelPosition position = m_label->getLabelPosition ();
        if (position == LabelPosition::TOP)
        {
            auto height = VeNo::Utils::getScaledSize (15);
            m_select->setBounds (0, height, getWidth (), getHeight () - height);
        }
        else if (position == LabelPosition::BOTTOM)
        {
            auto height = VeNo::Utils::getScaledSize (15);
            m_select->setBounds (0, 0, getWidth (), getHeight () - height);
        }
    }

    BaseComponent::resized ();
}

void VeNoSelect::paint (Graphics& g)
{
    BaseComponent::paint (g);
}
