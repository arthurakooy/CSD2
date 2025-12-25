#ifndef _FILTER_H_
#define _FILTER_H_
#include <iostream>

class Filter {
public:

    Filter(float cutoffFrequency, float samplerate = 44100);
    ~Filter();

    float processSample(float input);
    
    void setCutoff(float freq);
    
    void setSamplerate(float sr);
    
    void calculateAlpha();

protected:
    bool isFirstSample;
    float previousOutput;
    float alpha;
    float cutoffFrequency;
    float samplerate;
    float gainCompensation;
	const float pi = acos(-1);  //atan(1) * 4;
};

#endif