#ifndef _SYNTH_H_
#define _SYNTH_H_
#include <iostream>
#include "envelope.h"
#include <memory> 

class Synth {
public:
    Synth(float samplerate = 44100.0f);
    ~Synth();

    virtual void setSamplerate(float samplerate) = 0;
    void setAR(float attack, float release);

    virtual void playNote(float note, float amplitude) = 0;
    void noteOff();

    virtual void tick() = 0;
    float getSample();

protected:
    float sample;
    float samplerate;
    std::unique_ptr<Envelope> envelope;
};

#endif