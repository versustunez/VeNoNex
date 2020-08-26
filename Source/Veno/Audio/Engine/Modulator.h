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

    void setVoice(int voice);

    int getVoice ();

protected:
    float m_value = 0.0f;
    // if m_voice -1 this means he has not to add the value to a special voice like the Envelope
    int m_voice = -1;
};

#endif //VENO_MODULATOR_H
