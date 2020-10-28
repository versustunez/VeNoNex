#include "VeNoSelect.h"
#include "../../../Services/ComboBoxSetupHelper.h"
#include "../../../VenoInstance.h"
#include "../../../Utils.h"

VeNoSelect::VeNoSelect (const std::string& name, const std::string& pid)
        : BaseComponent (pid),
          m_select (std::make_unique<juce::ComboBox> ())
{
    m_select->setComponentID (name);
    m_select->setJustificationType (Justification::centredLeft);
    addAndMakeVisible (*m_select);
    auto instance = VenoInstance::getInstance (m_processId);
    if (instance->handler->getParameter (name) != nullptr)
    {
        auto treeState = instance->treeState;
        m_attachment = std::make_unique<ComboBoxAttachment> (*treeState, name, *m_select);
    }
    addAndMakeVisible (*m_select);
}

VeNoSelect::~VeNoSelect ()
{
    if (m_attachment != nullptr)
    {
        m_attachment.reset (nullptr);
    }
    m_select.reset ();
    if (m_label != nullptr)
    {
        m_label.reset ();
    }
}

void VeNoSelect::clearSelection ()
{
    m_select->clear (NotificationType::dontSendNotification);
    m_lastAddItem = 1;
}

int VeNoSelect::getSelection ()
{
    return m_select->getSelectedId ();
}


void VeNoSelect::addItem (const std::string& item)
{
    if (m_subMenu != nullptr)
    {
        m_subMenu->addItem (m_lastAddItem, item);
    }
    else
    {
        m_select->addItem (item, m_lastAddItem);
    }
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
            auto height = VeNo::Utils::getScaledSize (16);
            m_select->setBounds (0, height, getWidth (), getHeight () - height);
        }
        else if (position == LabelPosition::BOTTOM)
        {
            auto height = VeNo::Utils::getScaledSize (16);
            m_select->setBounds (0, 0, getWidth (), getHeight () - height);
        }
    }

    BaseComponent::resized ();
}

void VeNoSelect::paint (Graphics& g)
{
    BaseComponent::paint (g);
}

void VeNoSelect::addHeader (const std::string& item)
{

    if (m_subMenu != nullptr)
    {
        m_subMenu->addSectionHeader (item);
    }
    else
    {
        m_select->addSectionHeading (item);
    }
}

void VeNoSelect::addSeparator ()
{
    if (m_subMenu != nullptr)
    {
        m_subMenu->addSeparator();
    } else {
        m_select->addSeparator ();
    }
}

void VeNoSelect::startSubPath (std::string name)
{
    if (m_subMenu != nullptr)
    {
        closeSubPath ();
    }
    m_subMenu = std::make_shared<PopupMenu> ();
    m_subPathName = std::move(name);
}

void VeNoSelect::closeSubPath ()
{
    if (m_subMenu == nullptr)
        return;
    m_select->getRootMenu ()->addSubMenu (m_subPathName, *m_subMenu, true);
    m_subPathName = "";
    m_subMenu.reset ();
    m_subMenu = nullptr;
}
