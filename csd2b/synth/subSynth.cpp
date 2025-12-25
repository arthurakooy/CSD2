#include "subSynth.h"

SubSynth::SubSynth(float samplerate) : Synth(samplerate) {
    // std::cout << "SubSynth - constructor\n";
    filter = std::make_unique<Filter>(20000.0f, 44100.0f);
};

SubSynth::~SubSynth() {
    // std::cout << "SubSynth - destructor\n";
};

void SubSynth::setSamplerate(float samplerate) {
    for (auto& oscData : oscillators) {
        oscData.oscillator->setSamplerate(samplerate);
    }

    filter->setSamplerate(samplerate);

    this->samplerate = samplerate;
};

void SubSynth::addOscillator(std::string type, float level, float detune) {
    OscillatorData oscData;
    oscData.level = level;
    oscData.detune = detune;

    if(type == "sine") {
        oscData.oscillator = std::make_unique<Sine>(0.0f, samplerate);
    }
    else if(type == "saw") {
        oscData.oscillator = std::make_unique<Saw>(0.0f, samplerate);
    }
    else if(type == "square") {
        oscData.oscillator = std::make_unique<Square>(0.0f, samplerate);
    }
    else {std::cout << "oopsie woopsie";}

    oscillators.push_back(std::move(oscData));

    // std::cout << "added " << type << "\n";
}; 

void SubSynth::setFilterCutoff(float cutOffFrequency) {
    filter->setCutoff(cutOffFrequency);
}

void SubSynth::clearOscillators() {
    oscillators.clear();
    // std::cout << "Oscillators cleard\n";
};

void SubSynth::tick() {
    envelope->tick();

    float mixed = 0.0f;

    for(auto& oscData : oscillators) {
        mixed += oscData.oscillator->getSample() * oscData.level;
        oscData.oscillator->tick();
    }

    sample = mixed / oscillators.size();
    sample = sample * envelope->getAmplitude();

};

void SubSynth::playNote(float note, float amplitude) {
    for(auto& oscData : oscillators) {
        float detunedNote = note + oscData.detune;
        float freq = 440 * pow(2, (detunedNote - 69) / 12);
        oscData.oscillator->setFrequency(freq);
        oscData.oscillator->setAmplitude(amplitude);
    }
    envelope->triggerAttack();
};