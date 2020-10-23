#pragma once

#include "../BaseComponent.h"
#include "GuiMatrixItem.h"

namespace VeNo
{
    class GuiMatrixList : public BaseComponent
    {
    public:
        explicit GuiMatrixList(std::string& pid);
        ~GuiMatrixList() override;

        void resized () override;

        void paint (Graphics& g) override;

        void update();

        void addSlot(std::string key);

    protected:
        std::vector<std::unique_ptr<GuiMatrixItem>> m_items;
    };
}