#ifndef _SUBSYNTH_H_
#define _SUBSYNTH_H_
#include <iostream>
#include <memory>    // voor std::unique_ptr
#include <vector>    // voor std::vector
#include <string>    // voor std::string
#include <cmath>
#include "synth.h"
#include "filter.h"
#include "oscillator.h"
#include "sine.h"
#include "square.h"
#include "saw.h"

class SubSynth : public Synth {
public:
    SubSynth(float samplerate = 44100.0f);
    ~SubSynth();

    struct OscillatorData {
        std::unique_ptr<Oscillator> oscillator;
        float detune = 0.0f;     // Detune in semitones
        float level = 0.5f;
    };

    void tick() override;
    void setSamplerate(float samplerate) override;

    void playNote(float note, float amplitude) override;

    // Oscillator management
    void addOscillator(std::string type, float level, float detune);
    void clearOscillators();

    // Filter management
    void setFilterCutoff(float cutOffFrequency);


protected:
    std::vector<OscillatorData> oscillators;
    std::unique_ptr<Filter> filter;
};

#endif