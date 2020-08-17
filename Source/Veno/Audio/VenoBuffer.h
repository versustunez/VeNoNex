//
// Created by versustune on 12.06.20.
//

#ifndef VENO_VENOBUFFER_H
#define VENO_VENOBUFFER_H

#include <vector>
#include "JuceHeader.h"

class VenoBuffer
{
private:
    std::vector<float> m_buffer;
    std::vector<float> m_right;
    std::vector<float> m_left;
    std::vector<float> m_bufferCopy;
    std::vector<float> m_rightCopy;
    std::vector<float> m_leftCopy;
    int m_bufferSize = 2048;
    bool m_isOverflow = false;
public:
    VenoBuffer ();
    ~VenoBuffer ();
    void reset (int size);
    void addMonoSample (float value);
    void addLeftSample (float value);
    void addRightSample (float value);
    void calcPeak ();
    float leftPeak;
    float rightPeak;
    float monoPeak;
    const std::vector<float>& getBuffer () const;
protected:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (VenoBuffer);
};
#endif //VENO_VENOBUFFER_H
