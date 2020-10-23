#include "GuiMatrixList.h"
#include "../../../VenoInstance.h"

namespace VeNo
{
    GuiMatrixList::GuiMatrixList (std::string& pid)
            : BaseComponent (pid)
    {
        auto matrix = VenoInstance::getInstance (m_processId)->matrix;
        auto slots = matrix->getSlots ();
        for (auto& slot : slots)
        {
            addSlot (std::string(slot.first.c_str()));
        }
    }

    GuiMatrixList::~GuiMatrixList ()
    {
        removeAllChildren ();
        m_items.clear ();
    }

    void GuiMatrixList::resized ()
    {
        int y = 0;
        for (auto& item : m_items)
        {
            item->setBounds (0, y, getWidth (), 100);
            y += 100;
        }
    }

    void GuiMatrixList::paint (Graphics& g)
    {
        g.setColour(Config::getInstance()->getCurrentTheme()->getColour(ThemeColour::bg));
        g.fillAll();
    }

    void GuiMatrixList::update ()
    {
        auto matrix = VenoInstance::getInstance (m_processId)->matrix;
        auto slots = matrix->getSlots ();
        for (int i = m_items.size () - 1; i >= 0; i--)
        {
            auto& item = m_items[i];
            if (!slots.contains (item->m_key))
            {
                removeChildComponent (item.get ());
                item.reset (nullptr);
                m_items.erase (m_items.begin () + i);
            }
        }
        auto newHeight = m_items.size () * 100;
        if (newHeight > 700)
        {
            setSize (getWidth (), m_items.size () * 100);
        } else
        {
            resized();
        }
    }

    void GuiMatrixList::addSlot (std::string key)
    {
        m_items.push_back (std::make_unique<GuiMatrixItem> (m_processId, key));
        auto& item = m_items[m_items.size () - 1];
        addAndMakeVisible (*item);
        auto newHeight = m_items.size () * 100;
        if (newHeight > 700)
        {
            setSize (getWidth (), m_items.size () * 100);
        } else
        {
            resized();
        }
    }
}