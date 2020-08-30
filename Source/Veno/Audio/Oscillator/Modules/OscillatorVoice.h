#ifndef VENO_OSCILLATORVOICE_H
#define VENO_OSCILLATORVOICE_H

#include <string>
#include <memory>
#include <vector>
#include "../Helper/WaveTableWrapper.h"
#include "Widener.h"
#include "../Helper/DetuneHelper.h"

class OscillatorVoice
{
private:
    std::string m_id;
    std::shared_ptr<WaveTableWrapper> m_waveTableWrapper;
    std::shared_ptr<DetuneHelper> m_detuneHelper;
    std::shared_ptr<Widener> m_widener;
    int m_index = 0;
    std::vector<float> m_values{0, 0, 0};
    bool m_isCenter = false;
    bool m_isLeft = false;
public:
    explicit OscillatorVoice (const std::string& id, std::shared_ptr<WaveTableWrapper>& waveTableWrapper,
                              std::shared_ptr<DetuneHelper>& detuneHelper,
                              std::shared_ptr<Widener>& widener, int index);

    ~OscillatorVoice ();

    void processValue (float freq);

    float getLeftValue ();

    float getRightValue ();

    float getMonoValue ();

    bool m_isMono = false;
protected:
};


#endif //VENO_OSCILLATORVOICE_H
