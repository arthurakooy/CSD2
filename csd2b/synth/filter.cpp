#include "filter.h"
#include <iostream>
#include <cmath>
#include "math.h"

Filter::Filter(float cutoffFrequency, float samplerate) : 
    samplerate(samplerate), 
    cutoffFrequency(cutoffFrequency), 
    alpha(0.5), previousOutput(0.0),
    isFirstSample(true)
{
    calculateAlpha();
    // std::cout << "Filter - constructor\n";
}

Filter::~Filter() {
    // std::cout << "Filter - destructor\n";
}

float Filter::processSample(float input) {
    // std::cout << "=== FILTER DEBUG ===" << std::endl;
    // std::cout << "isFirstSample: " << isFirstSample << std::endl;
    // std::cout << "alpha: " << alpha << std::endl;
    // std::cout << "previousOutput: " << previousOutput << std::endl;
    // std::cout << "input: " << input << std::endl;

    // initialize filter with first sample because previousOutput can't be 0
    if (isFirstSample) {
        previousOutput = input;
        isFirstSample = false;
        return input; // first sample remains unchanged
    }
    
    //float output = alpha * input + (1.0f - alpha) * previousOutput;
    float output = previousOutput + alpha * (input - previousOutput);

    previousOutput = output;

    return output;
}

void Filter::calculateAlpha() {
    if (cutoffFrequency <= 0.0f || samplerate <= 0.0f) {
        alpha = 1.0f;
        return;
    }

    // works, idk how, idk why
    float dt = 1.0 / samplerate;
    float RC = 1.0 / (2 * pi * cutoffFrequency);
    alpha = dt / (dt + RC);

    // std::cout << "alpha=" << alpha << std::endl;
}

void Filter::setCutoff(float freq) {
    this->cutoffFrequency = freq;
    calculateAlpha();
    isFirstSample = true;
}

void Filter::setSamplerate(float sr) {
    this->samplerate = sr;
    calculateAlpha();
    isFirstSample = true;
}

