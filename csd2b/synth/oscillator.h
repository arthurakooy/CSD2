#ifndef _OSCILLATOR_H_
#define _OSCILLATOR_H_
#include <iostream>
#include <cmath> 

class Oscillator {
public:
	//constructors and destructors
	Oscillator(float frequency, float samplerate = 44100);
	~Oscillator();

	//methods
	void setSamplerate(float samplerate);
	//return the current sample
	float getSample();

	void updatePhase();
	virtual float calculateSample() = 0; //is overwritten by child class
	void tick();

	//getters and setters
	void setFrequency(float f);
	float getFrequency();
	void setAmplitude(float a);
	float getAmplitude();
	float getPhase();

protected:
	const float pi = acos(-1);  //atan(1) * 4; <-- vak van Pieter.
	float frequency;
	float amplitude;
	float phase;
	// sample contains the current sample
	float sample;
	float samplerate;
	float phaseIncrement;
};

#endif