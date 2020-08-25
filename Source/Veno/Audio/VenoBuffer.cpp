#include <cmath>
#include "VenoBuffer.h"
#include "../Utils.h"
#include "../VenoInstance.h"

VenoBuffer::VenoBuffer (const std::string& id)
{
    m_bufferCopy.resize (m_bufferSize);
    m_rightCopy.resize (m_bufferSize);
    m_leftCopy.resize (m_bufferSize);
    m_buffer.resize (m_bufferSize);
    m_right.resize (m_bufferSize);
    m_left.resize (m_bufferSize);
    m_id = id;
}

VenoBuffer::~VenoBuffer ()
{
    m_buffer.clear ();
    m_right.clear ();
    m_left.clear ();
    m_bufferCopy.clear ();
    m_rightCopy.clear ();
    m_leftCopy.clear ();
}

void VenoBuffer::reset (int size)
{
    if (m_isOverflow)
    {
        calcPeak ();
        m_isOverflow = false;
    }
}

void VenoBuffer::addMonoSample (float value)
{
    if (m_buffer.size () > m_bufferSize)
    {
        for (int i = 0; i < m_bufferSize; ++i)
        {
            m_bufferCopy[i] = m_buffer[i];
        }
        VenoInstance::getInstance (m_id)->changeListener->notifyListener ("waveform", std::abs (m_highestPeak));
        m_highestPeak = 0;
        m_buffer.clear ();
        m_isOverflow = true;
    }
    if (std::abs (value) > m_highestPeak)
    {
        m_highestPeak = value;
    }
    m_buffer.push_back (value);
}

void VenoBuffer::addLeftSample (float value)
{
    if (m_left.size () > m_bufferSize)
    {
        for (int i = 0; i < m_bufferSize; ++i)
        {
            m_leftCopy[i] = m_left[i];
        }
        m_left.clear ();
        m_isOverflow = true;
    }
    m_left.push_back (value);
}

void VenoBuffer::addRightSample (float value)
{
    if (m_right.size () > m_bufferSize)
    {
        for (int i = 0; i < m_bufferSize; ++i)
        {
            m_rightCopy[i] = m_right[i];
        }
        m_right.clear ();
        m_isOverflow = true;
    }
    m_right.push_back (value);
}

void VenoBuffer::calcPeak ()
{
    float leftRMS = 0;
    float rightRMS = 0;
    auto size = m_bufferCopy.size ();
    for (int i = 0; i < size; ++i)
    {
        leftRMS += m_leftCopy[i] * m_leftCopy[i];
        rightRMS += m_rightCopy[i] * m_rightCopy[i];
    }
    rightPeak = VeNo::Utils::clamp (Decibels::gainToDecibels (std::sqrt (rightRMS / size), -30.0f), -30.0f, 0.0f);
    leftPeak = VeNo::Utils::clamp (Decibels::gainToDecibels (std::sqrt (leftRMS / size), -30.0f), -30.0f, 0.0f);
    monoPeak = leftPeak;
}

const std::vector<float>& VenoBuffer::getBuffer () const
{
    return m_bufferCopy;
}