//
// Created by versustune on 12.06.20.
//

#include <cmath>
#include "VenoBuffer.h"

VenoBuffer::VenoBuffer ()
{

}

VenoBuffer::~VenoBuffer ()
{
    buffer.clear();
    right.clear();
    left.clear();
}

void VenoBuffer::reset (int size)
{
    if (size != buffer.size())
    {
        buffer.resize(size);
        right.resize(size);
        left.resize(size);
    }
    // reset to 0 dc :D
    for (int i = 0; i < size; ++i)
    {
        buffer[i] = 0;
        left[i] = 0;
        right[i] = 0;
    }
    leftPeak = 0;
    rightPeak = 0;
    monoPeak = 0;
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
    for (int i = 0; i < buffer.size(); ++i)
    {
        auto l = std::abs(left[i]);
        auto r = std::abs(right[i]);
        auto m = std::abs(buffer[i]);
        if (m > monoPeak)
        {
            monoPeak = m;
        }
        if (l > leftPeak)
        {
            leftPeak = l;
        }
        if (r > rightPeak)
        {
            rightPeak = r;
        }
    }
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
