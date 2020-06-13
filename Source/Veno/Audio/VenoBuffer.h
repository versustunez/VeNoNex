//
// Created by versustune on 12.06.20.
//

#ifndef VENO_VENOBUFFER_H
#define VENO_VENOBUFFER_H

#include <vector>

class VenoBuffer
{
private:
    std::vector<float> buffer;
    std::vector<float> right;
    std::vector<float> left;
public:
    VenoBuffer ();
    ~VenoBuffer ();
    void reset (int size);
    void addMonoSample (float value, int index);
    void addLeftSample (float value, int index);
    void addRightSample (float value, int index);
    void calcPeak ();
    float leftPeak;
    float rightPeak;
    float monoPeak;
    const std::vector<float>& getBuffer () const;
    const std::vector<float>& getRight () const;
    const std::vector<float>& getLeft () const;
};
#endif //VENO_VENOBUFFER_H
