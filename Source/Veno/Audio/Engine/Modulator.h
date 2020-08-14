//
// Created by versustune on 13.06.20.
//

#ifndef VENO_MODULATOR_H
#define VENO_MODULATOR_H
// class that define if it can be a modulator on not
// like LFO, Envelope, maybe also OSCILLATORS :P VELOCITY AND OTHER STUFF IS ALSO A MODULATOR!
class Modulator
{
public:
    Modulator ();
    virtual ~Modulator ();
    virtual float getValue ();
    virtual void update ();
protected:
    float m_value;
};
#endif //VENO_MODULATOR_H
