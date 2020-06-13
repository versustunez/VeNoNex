//
// Created by versustune on 11.06.20.
//

#ifndef VENO_SIDEBARLCD_H
#define VENO_SIDEBARLCD_H

#include "JuceHeader.h"
#include "../BaseComponent.h"
#include "Waveforms.h"

class SidebarLCD : public BaseComponent {
private:
    int m_innerX = 5;
    int m_innerY = 5;
    int m_width = m_innerX * 2;
public:
    explicit SidebarLCD(const std::string &process_id);
    ~SidebarLCD();

    void resized() override;
    void paint(Graphics &g) override;

protected:
    void drawHeadline(Graphics &g);
    void drawFooter(Graphics &g);

    std::unique_ptr<Waveforms> waveform;
};


#endif //VENO_SIDEBARLCD_H
