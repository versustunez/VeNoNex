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
    int m_index;
    std::vector<double> m_values{0, 0, 0};
    bool m_isCenter;
    bool m_isLeft;
public:
    explicit OscillatorVoice (const std::string& id, std::shared_ptr<WaveTableWrapper>& waveTableWrapper,
                              std::shared_ptr<DetuneHelper>& detuneHelper,
                              std::shared_ptr<Widener>& widener, int index);

    ~OscillatorVoice ();

    void processValue ();

    double getLeftValue ();

    double getRightValue ();

    double getMonoValue ();

    bool m_isMono = false;
protected:
};


#endif //VENO_OSCILLATORVOICE_H
