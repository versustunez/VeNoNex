#include "LCDParameters.h"
#include "../../../../Utils.h"
#include "../../../../Core/Config.h"
#include "../../../Fonts/Fonts.h"

namespace VeNo
{
    LCDParameters::LCDParameters (std::string& pid)
            : BaseComponent (pid)
    {
        setMouseCursor (MouseCursor::PointingHandCursor);
        std::srand (unsigned (time (nullptr)));
        m_randomText = (std::rand () % RANDOM_TEXT_COUNT);
    }

    LCDParameters::~LCDParameters ()
    {
        stopTimer ();
    }

    void LCDParameters::parameterChanged (VeNoParameter* parameter)
    {
        if (m_isStarting)
        {
            return;
        }
        m_changedParameter = parameter->getShowName ();
        m_changedValue = parameter->getBaseValue ();
        m_isChangingData = true;
        m_ticks = 0;
        startTimer (16);
    }

    void LCDParameters::notify (const std::string& name, double value)
    {

    }

    void LCDParameters::resized ()
    {
    }

    void LCDParameters::paint (Graphics& g)
    {
        if (!m_isStarting && !m_isChangingData)
        {
            g.setOpacity(0);
            stopTimer ();
            return;
        }
        auto theme = Config::getInstance ()->getCurrentTheme ();
        g.fillAll (theme->getColour (ThemeColour::lcd_bg));
        auto accent = theme->getColour (ThemeColour::lcd);
        g.setColour (accent);
        g.setFont (*VenoFonts::getLCD ());
        VeNo::Utils::setFontSize (16.0f, g);
        if (m_isStarting)
        {
            g.drawText (m_warmUpText[m_randomText], 0, 0, getWidth (), getHeight (),
                        juce::Justification::centred, true);
        }
        else if (m_isChangingData)
        {
            int halfHeight = getHeight () / 2;
            int font = (int) VeNo::Utils::setFontSize (12, g);
            g.drawText (m_changedParameter, 0, halfHeight - font, getWidth (), font, Justification::centred, true);
            g.drawText (std::to_string (m_changedValue), 0, halfHeight + 4, getWidth (), font, Justification::centred,
                        true);
        }
        m_ticks++;
        if (m_ticks > m_time_needed)
        {
            m_isStarting = false;
            m_isChangingData = false;
        }
    }

    void LCDParameters::timerCallback ()
    {
        repaint ();
    }

    void LCDParameters::setIsStarting ()
    {
        m_isStarting = true;
        m_ticks = 0;
        startTimer (16);
    }
}