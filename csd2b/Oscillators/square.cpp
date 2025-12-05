#include "square.h"
#include "math.h"

Square::Square(float frequency, float samplerate) : Oscillator(frequency, samplerate) {
  std::cout << "Square - constructor\n";
}

Square::~Square() {
  std::cout << "Square - destructor\n";
}

float Square::calculateSample() {
	return (phase < 0.5f) ? amplitude : -amplitude;
}
