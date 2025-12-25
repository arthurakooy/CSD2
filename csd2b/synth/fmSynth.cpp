#include <string>
#include "fmSynth.h"

FmSynth::FmSynth(float samplerate) : Synth(samplerate),
    modulationIndex(1.0f),
    ratio(0.5)
{
    carrierOsc = std::make_unique<Sine>(0.0f, samplerate);
    modulatorOsc = std::make_unique<Sine>(0.0f, samplerate);
    modulatorOsc->setAmplitude(1.0);

    // std::cout << "FmSynth - constructor\n";
};

FmSynth::~FmSynth() {
    // std::cout << "FmSynth - destructor\n";
};

void FmSynth::setSamplerate(float samplerate) {
    this->samplerate = samplerate;
    carrierOsc->setSamplerate(samplerate);
    modulatorOsc->setSamplerate(samplerate);
};

void FmSynth::tick() {
    envelope->tick();

    //tick and calculate modulaor sample
    modulatorOsc->tick();
    float modSample = modulatorOsc->getSample();

    //update carrier phase
    carrierOsc->updatePhase();

    //calculate modulated phase
    float modulatedPhase = carrierOsc->getPhase() + (modSample * modulationIndex);
    modulatedPhase = fmod(modulatedPhase, 1.0f);

    sample = carrierOsc->calculateSampleAtPhase(modulatedPhase);
    sample *= envelope->getAmplitude();
};

void FmSynth::playNote(float note, float amplitude) {
    float freq = 440 * pow(2, (note - 69) / 12);
    carrierOsc->setFrequency(freq);
    modulatorOsc->setFrequency(freq * ratio);
    carrierOsc->setAmplitude(amplitude);
    envelope->triggerAttack();
};

void FmSynth::setRatio(float ratio) {
    this->ratio = ratio;
    // Update modulator freq if a note is active
    if (carrierOsc->getFrequency() > 0.0f) {
        modulatorOsc->setFrequency(carrierOsc->getFrequency() * ratio);
    }
};

void FmSynth::setModulationIndex(float modulationIndex) {
    this->modulationIndex = modulationIndex;
};

// #TODO implement different waveforms

// void FmSynth::setCarrier(std::string type) {
//     if(type == "sine") {
//         carrierOsc = std::make_unique<Sine>(0.0f, samplerate);
//     }
//     else if(type == "saw") {
//         carrierOsc = std::make_unique<Saw>(0.0f, samplerate);
//     }
//     else if(type == "square") {
//         carrierOsc = std::make_unique<Square>(0.0f, samplerate);
//     }
//     else {std::cout << "oopsie woopsie, type invalid :((";}
// }; 

// void FmSynth::setModulator(std::string type) {
//     if(type == "sine") {
//         modulatorOsc = std::make_unique<Sine>(0.0f, samplerate);
//     }
//     else if(type == "saw") {
//         modulatorOsc = std::make_unique<Saw>(0.0f, samplerate);
//     }
//     else if(type == "square") {
//         modulatorOsc = std::make_unique<Square>(0.0f, samplerate);
//     }
//     else {std::cout << "oopsie woopsie, type invalid :((";}
// }; 