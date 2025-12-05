#ifndef _SQUARE_H_
#define _SQUARE_H_
#include <iostream>
#include <cmath>
#include "oscillator.h"

class Square : public Oscillator {
public:
	//Constructor and destructor
	Square(float frequency, float samplerate = 44100);
	~Square();

	float calculateSample() override;

	// go to next sample
	//void tick();
};
#endif