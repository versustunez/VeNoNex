#include "GUILimiter.h"

namespace VeNo
{
    GUILimiter::GUILimiter (const std::string& name, const std::string& pid)
            : BaseComponent (pid), m_name (name)
    {
    }

    void GUILimiter::resized ()
    {
    }

    void GUILimiter::paint (Graphics& g)
    {
    }
}