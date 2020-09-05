#include "Pitch.h"

namespace VeNo
{
    Pitch::Pitch (const std::string& name, const std::string& pid)
            : BaseComponent (pid), m_name (name)
    {
    }

    void Pitch::resized ()
    {
    }

    void Pitch::paint (Graphics& g)
    {
    }
}