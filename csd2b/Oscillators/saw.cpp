#include "saw.h"
#include "math.h"

Saw::Saw(float frequency, float samplerate) : Oscillator(frequency, samplerate) {
  std::cout << "Saw - constructor\n";
}

Saw::~Saw() {
  std::cout << "Saw - destructor\n";
}

float Saw::calculateSample() {
    return (2.0f * phase - 1.0f) * amplitude;
}