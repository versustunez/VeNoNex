#ifndef VENO_VENOBUFFER_H
#define VENO_VENOBUFFER_H

#include <vector>
#include "JuceHeader.h"

class VenoBuffer
{
private:
    std::vector<double> m_buffer;
    std::vector<double> m_right;
    std::vector<double> m_left;
    std::vector<double> m_bufferCopy;
    std::vector<double> m_rightCopy;
    std::vector<double> m_leftCopy;
    int m_bufferSize = 2048;
    bool m_isOverflow = false;
    std::string m_id;

    void addSample(double, std::vector<double>&, std::vector<double>&);
public:
    VenoBuffer (const std::string& id);

    ~VenoBuffer ();

    void reset (int size);

    void addMonoSample (double value);

    void addLeftSample (double value);

    void addRightSample (double value);

    void calcPeak ();

    double leftPeak{};
    double rightPeak{};
    std::string m_wave = "waveform";
    const std::vector<double>& getBuffer () const;

protected:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (VenoBuffer);
};

#endif //VENO_VENOBUFFER_H
