#include "VeNoSelect.h"
#include "../../../Utils/ComboBoxSetupHelper.h"
#include "../../../VenoInstance.h"

VeNoSelect::VeNoSelect (const std::string& name, const std::string& pid)
        : BaseComponent (pid)
{
    m_select->setComponentID (name);
    addAndMakeVisible (*m_select);
    auto treeState = VenoInstance::getInstance (m_processId)->treeState;
    m_attachment = std::make_unique<ComboBoxAttachment> (*treeState, name, *m_select);
}

VeNoSelect::~VeNoSelect ()
{
    m_attachment.reset (nullptr);
    m_select.reset ();
    BaseComponent::~BaseComponent ();
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
    BaseComponent::resized ();
}

void VeNoSelect::paint (Graphics& g)
{
    BaseComponent::paint (g);
}
