#pragma once

#include <string>
#include "../GUI/Components/BaseComponent.h"
#include "../GUI/Components/Base/VeNoSelect.h"

namespace VeNo
{
    struct GUIItem
    {
        std::string type;
        std::string parameter;
        std::string name;
        int x;
        int y;
        int w;
        int h;
        VeNoSelect::Type selectType;
        BaseComponent* component;
    };

    struct BlockStruct
    {
        std::string name;
        int x;
        int y;
        int w;
        int h;
    };

    class GUIHelper {
    public:
        GUIHelper(std::string pid, std::string name);
        ~GUIHelper();
        std::vector<BlockStruct> m_blocks;
        std::vector<GUIItem> m_gui_parts;
        void createItem(GUIItem item);

    protected:
        std::string m_pid;
        std::string m_name;
    };
}