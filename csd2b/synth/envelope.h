#ifndef _ENVELOPE_H_
#define _ENVELOPE_H_

#include <iostream>
// simple attack/release envelope
class Envelope {
public:
    Envelope(float attackTime, float releaseTime, float samplerate);
    ~Envelope();

    void triggerAttack();
    void triggerRelease();

    float getAmplitude();
    void tick();
    void setAR(float attack, float release);

private:
    float samplerate;
    float amplitude;
    float attackTime;
    float releaseTime;
    float increment;
    int envelopeSamples;
    int currentSample;
};

#endif