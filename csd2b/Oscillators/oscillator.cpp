#include "oscillator.h"

Oscillator::Oscillator(float frequency, float samplerate) : frequency(frequency),
amplitude(1.0), phase(0), sample(0), samplerate(samplerate), phaseIncrement(frequency / samplerate)
{
	std::cout << "Oscillator - constructor\n";
}

Oscillator::~Oscillator() {
	std::cout << "Oscillator - destructor\n";
}

void Oscillator::setSamplerate(float samplerate) { 
	this->samplerate = samplerate; 
	this->phaseIncrement = frequency / samplerate;
}

float Oscillator::getSample() { return sample; }

//calculate phase based on increment
void Oscillator::updatePhase() {
	phase += phaseIncrement;
	if (phase > 1.0f) {
		phase -= 1.0f;
	}
}

void Oscillator::tick() {
	updatePhase();
	sample = calculateSample();
}

//getters and setters

float Oscillator::getFrequency() { return frequency; }
void Oscillator::setFrequency(float f) { 
	this->frequency = f;
	this->phaseIncrement = frequency / samplerate;
}

float Oscillator::getAmplitude() { return amplitude; }
void Oscillator::setAmplitude(float a) { this->amplitude = a; }