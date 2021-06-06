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

void VenoBuffer::addSample (double value, std::vector<double> &where, std::vector<double> &copy)
{
    if (where.size () > m_bufferSize)
    {
        for (int i = 0; i < m_bufferSize; ++i)
        {
            copy[i] = where[i];
        }
        VenoInstance::getInstance (m_id)->changeListener->notifyListener (m_wave, 1);
        where.clear ();
        m_isOverflow = true;
    }
    where.push_back (value);
}

void VenoBuffer::addMonoSample (double value)
{
    addSample (value, m_buffer, m_bufferCopy);
}

void VenoBuffer::addLeftSample (double value)
{
    addSample (value, m_left, m_leftCopy);
}

void VenoBuffer::addRightSample (double value)
{
    addSample (value, m_right, m_rightCopy);
}

double calcChannelPeak(double mean) {
    return VeNo::Utils::clamp(Decibels::gainToDecibels(std::sqrt(mean), -30.0), -30.0, 0.0);
}

void VenoBuffer::calcPeak ()
{
    double leftRMS = 0;
    double rightRMS = 0;
    auto size = m_bufferCopy.size ();
    for (int i = 0; i < size; ++i)
    {
        leftRMS += m_leftCopy[i] * m_leftCopy[i];
        rightRMS += m_rightCopy[i] * m_rightCopy[i];
    }
    rightPeak = calcChannelPeak (rightRMS / size);
    leftPeak = calcChannelPeak (leftRMS / size);
}

const std::vector<double>& VenoBuffer::getBuffer () const
{
    return m_bufferCopy;
}