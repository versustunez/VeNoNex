//
// Created by versustune on 12.06.20.
//

#include <cmath>
#include "VenoBuffer.h"
#include "../Utils.h"

VenoBuffer::VenoBuffer ()
{

}

VenoBuffer::~VenoBuffer ()
{
    buffer.clear ();
    right.clear ();
    left.clear ();
}

void VenoBuffer::reset (int size)
{
    if (size != buffer.size ())
    {
        buffer.resize (size);
        right.resize (size);
        left.resize (size);
    }
    // reset to 0 dc :D
    for (int i = 0; i < size; ++i)
    {
        buffer[i] = 0;
        left[i] = 0;
        right[i] = 0;
    }
    leftPeak = -30;
    rightPeak = -30;
    monoPeak = -30;
}

void VenoBuffer::addMonoSample (float value, int index)
{
    buffer[index] = value;
}

void VenoBuffer::addLeftSample (float value, int index)
{
    left[index] = value;
}

void VenoBuffer::addRightSample (float value, int index)
{
    right[index] = value;
}

void VenoBuffer::calcPeak ()
{
    float leftRMS = 0;
    float rightRMS = 0;
    auto size = buffer.size();
    for (int i = 0; i < size; ++i)
    {
        leftRMS += left[i] * left[i];
        rightRMS += right[i] * right[i];
    }
    rightPeak = VeNo::Utils::clamp (Decibels::gainToDecibels (std::sqrt (rightRMS / size), -30.0f), -30.0f, 0.0f);
    leftPeak = VeNo::Utils::clamp (Decibels::gainToDecibels (std::sqrt (leftRMS / size), -30.0f), -30.0f, 0.0f);
    monoPeak = leftPeak;
}

const std::vector<float>& VenoBuffer::getBuffer () const
{
    return buffer;
}

const std::vector<float>& VenoBuffer::getRight () const
{
    return right;
}

const std::vector<float>& VenoBuffer::getLeft () const
{
    return left;
}
