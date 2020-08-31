#include "Modulator.h"

double Modulator::getValue ()
{
    return m_value;
}

Modulator::Modulator ()
= default;

Modulator::~Modulator ()
= default;

void Modulator::update ()
{
}

void Modulator::setVoice (int voice)
{
    m_voice = voice;
}

int Modulator::getVoice ()
{
    return m_voice;
}
