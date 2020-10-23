#include "VeNoComponentListener.h"
#include "../../../VenoInstance.h"

#include <utility>

VeNoComponentListener::VeNoComponentListener (std::string pid)
        : m_pid (std::move (pid))
{
}

void VeNoComponentListener::buttonClicked (Button* button)
{
}

void VeNoComponentListener::comboBoxChanged (ComboBox* comboBoxThatHasChanged)
{
}

void VeNoComponentListener::sliderValueChanged (Slider* slider)
{
    if (m_sliderChanging)
    {
        auto instance = VenoInstance::getInstance (m_pid);
        auto parameter = instance->handler->getParameter (slider->getName ().toStdString ());
        instance->changeListener->notifyParameterChanged ("waveform", parameter);
    }

}

void VeNoComponentListener::sliderDragEnded (Slider* slider)
{
    m_sliderChanging = false;
}

void VeNoComponentListener::sliderDragStarted (Slider* slider)
{
    m_sliderChanging = true;
}
