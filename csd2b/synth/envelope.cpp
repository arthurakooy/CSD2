#include "envelope.h"

Envelope::Envelope(float attackTime, float releaseTime, float samplerate) : 
    attackTime(attackTime), 
    releaseTime(releaseTime), 
    samplerate(samplerate),
    amplitude(0.0f),
    currentSample(0),
    envelopeSamples(0),
    increment(0.0f)
{
    // std::cout << "Envelope - constructor\n";
}

Envelope::~Envelope() {
    // std::cout << "Envelope - destructor\n";
}

float Envelope::getAmplitude() { 
    return amplitude; 
}

void Envelope::tick() {
    if(currentSample < envelopeSamples) {
        amplitude += increment;
        currentSample++;

        if (amplitude < 0.0f) amplitude = 0.0f;
        if (amplitude > 1.0f) amplitude = 1.0f;
    }
}

void Envelope::triggerAttack() {
    currentSample = 0;
    envelopeSamples = attackTime * samplerate;
    increment = (1.0f - amplitude) / envelopeSamples;
}

void Envelope::triggerRelease() {
    currentSample = 0;
    envelopeSamples = releaseTime * samplerate;
    increment = (0.0f - amplitude) / envelopeSamples;
}

void Envelope::setAR(float attack, float release) {
    this->attackTime = attack;
    this->releaseTime = release;
}