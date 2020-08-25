#ifndef VENO_LOOKHANDLER_H
#define VENO_LOOKHANDLER_H

#include "JuceHeader.h"
#include "CrazyLook.h"
#include "FlatLook.h"
#include <memory>

/**
 * overwrite the basic m_look and feel based on the selected Look and Feel :)
 */
class LookHandler : public LookAndFeel_V4
{
private:
    std::shared_ptr<LookAndFeel_V4> m_look;
    int m_currentLook = 0;
public:
    LookHandler ();

    ~LookHandler () override;

    void selectLook (int index);

    LookAndFeel_V4* getLook ();

protected:
    //currently both available themes are CrazyLook <-- (this is a fun one xD) and FlatLook
    LookAndFeel_V4* m_feels[2] = {new FlatLook (), new CrazyLook ()};
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LookHandler);
};

#endif //VENO_LOOKHANDLER_H
