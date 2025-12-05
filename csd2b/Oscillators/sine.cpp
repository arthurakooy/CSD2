#include "sine.h"
#include "math.h"

Sine::Sine(float frequency, float samplerate) : Oscillator(frequency, samplerate) {
  std::cout << "Sine - constructor\n";
}

Sine::~Sine() {
  std::cout << "Sine - destructor\n";
}

float Sine::calculateSample() {
	return sin(pi * 2 * phase) * amplitude;
}

//void Sine::tick() {
//  // NOTE 1. - frequency / SAMPLERATE can be implemented in a more efficient way
//  phase += frequency / samplerate;
//  if(phase > 1.0f) {
//    phase -= 1.0f;
//  }
//  sample = sin(pi * 2 * phase) * amplitude;
//}