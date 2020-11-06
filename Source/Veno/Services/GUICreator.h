#pragma once

#include <string>
#include "../GUI/Components/BaseComponent.h"

namespace VeNo
{
    class GUICreator : public BaseComponent
    {
    public:
        explicit GUICreator (const std::string& pid);

        ~GUICreator () override = default;

        virtual void setupGui () = 0;

    protected:
    };
}