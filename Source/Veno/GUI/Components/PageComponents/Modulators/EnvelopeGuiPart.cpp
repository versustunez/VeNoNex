#include "EnvelopeGuiPart.h"

#include <utility>
#include "../../../../Core/Config.h"
#include "../../../../Utils.h"

namespace VeNo
{
    EnvelopeGuiPart::EnvelopeGuiPart (std::string label, std::string name, const std::string& pid)
            : GUICreator (pid), m_name (std::move(name)), m_label (std::move(label)),
              m_helper (std::make_unique<GUIHelper> (m_processId, m_name))
    {
        m_helper->makeVisible(this);
    }

    EnvelopeGuiPart::~EnvelopeGuiPart () = default;

    void EnvelopeGuiPart::resized ()
    {
        m_helper->resizeComponents();
    }

    void EnvelopeGuiPart::paint (Graphics& g)
    {
        auto theme = Config::getInstance ()->getCurrentTheme ();
        auto bgColor = theme->getColour (ThemeColour::bg);
        auto fontColor = theme->getColour (ThemeColour::font);
        auto fontSize = Utils::setFontSize (13, g);

        g.setColour (bgColor);
        g.fillRoundedRectangle (0, 0, getWidth (), getHeight (), Utils::getScaledSize (8));
        g.setColour (fontColor);
        g.drawText (m_label, 0, 0, getWidth (), fontSize, Justification::centred);
    }
}