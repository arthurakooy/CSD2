#include "synth.h"

Synth::Synth(float samplerate) : samplerate(samplerate) {
    envelope = std::make_unique<Envelope>(0.0f, 0.0f, samplerate);

    // std::cout << "Synth - constructor\n";
};

Synth::~Synth() {
    // std::cout << "Synth - destructor\n";
};

void Synth::setAR(float attack, float release) {
    envelope->setAR(attack, release);
};

void Synth::noteOff() {
    envelope->triggerRelease();
};

float Synth::getSample() {
    return sample;
};


