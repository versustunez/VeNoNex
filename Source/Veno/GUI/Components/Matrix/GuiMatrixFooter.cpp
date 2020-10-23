#include "GuiMatrixFooter.h"
#include "../../../Core/Config.h"
#include "../../../VenoInstance.h"

namespace VeNo
{
    GuiMatrixFooter::GuiMatrixFooter (std::string& pid)
            : BaseComponent (pid),
              m_modulatorSelect (std::make_unique<VeNoSelect> ("unknown", m_processId)),
              m_modulationSelect (std::make_unique<VeNoSelect> ("unknown", m_processId)),
              m_addButton (std::make_unique<VeNoTextButton> ("add_matrix", "Add to Matrix", m_processId))
    {
        m_modulatorSelect->init ("Modulator", LabelPosition::BOTTOM, VeNoSelect::Type::Free);
        m_modulationSelect->init ("To Modulate", LabelPosition::BOTTOM, VeNoSelect::Type::Free);
        m_addButton->m_button->addListener (this);
        addAndMakeVisible (*m_modulatorSelect);
        addAndMakeVisible (*m_modulationSelect);
        addAndMakeVisible (*m_addButton);
        initMatrix ();
    }

    GuiMatrixFooter::~GuiMatrixFooter ()
    {
        m_modulatorSelect.reset ();
        m_modulationSelect.reset ();
        m_addButton.reset ();
    }

    void GuiMatrixFooter::resized ()
    {
        m_modulatorSelect->setBounds (40, 10, 180, 80);
        m_modulationSelect->setBounds (265, 10, 180, 80);
        m_addButton->setBounds (600, 25, 180, 50);
    }

    void GuiMatrixFooter::paint (Graphics& g)
    {
        g.fillAll (Config::getInstance ()->getCurrentTheme ()->getColour (ThemeColour::bg_two));
    }

    void GuiMatrixFooter::initMatrix ()
    {
        m_modulationSelect->clearSelection ();
        m_modulatorSelect->clearSelection ();
        m_modulators.clear ();
        m_modulations.clear ();
        auto instance = VenoInstance::getInstance (m_processId);
        auto matrix = instance->matrix;
        auto parameters = instance->handler->getParameters ();
        auto params = instance->handler->rawParameters ();
        auto& modulators = matrix->getModulators ();
        auto& rawMods = matrix->m_rawOrder;
        for (auto& modulator : rawMods)
        {
            m_modulatorSelect->addItem (modulators.at (modulator)->m_showName);
            m_modulators.push_back (modulator);
        }
        for (auto& param : params)
        {
            auto parameter = parameters[param];
            if (parameter == nullptr)
            {
                continue;
            }
            if (parameters[param]->getModulateValue () != nullptr)
            {
                m_modulationSelect->addItem (parameter->getShowName ());
                m_modulations.push_back (param);
            }
        }
    }

    void GuiMatrixFooter::buttonClicked (Button* button)
    {
        auto valSelect = m_modulationSelect->getSelection ();
        auto modSelect = m_modulatorSelect->getSelection ();
        if (valSelect == 0 || modSelect == 0)
        {
            return;
        }
        auto modulation = m_modulations[valSelect - 1];
        auto modulatorSelect = m_modulators[modSelect - 1];
        auto instance = VenoInstance::getInstance (m_processId);
        auto matrix = instance->matrix;
        if (matrix->setMatrixModulation (modulation, modulatorSelect, 0))
        {
            auto c = std::string (modulatorSelect + modulation);
            instance->state->matrix->m_component->m_list->addSlot (c);
        };
        m_modulatorSelect->select (0);
        m_modulationSelect->select (0);

    }

    void GuiMatrixFooter::buttonStateChanged (Button* button)
    {
    }
}