#include "audiocomponent.h"
//  Daan Schrier
#include "subSynth.h"
#include "fmSynth.h"
#include "synth.h"
#include <memory>

struct CustomCallback : AudioCallback {
    explicit CustomCallback (double Fs) : AudioCallback(Fs) {
        // synth.setSamplerate(Fs);

        // // test stuffz
        // synth.addOscillator("saw", 0.8f, 0.0f);
        // synth.addOscillator("square", 0.5f, -12.0f);
        // synth.setAR(2.0f, 1.0f);
        // synth.setFilterCutoff(2000.0f);

        synth = std::make_unique<FmSynth>(Fs);
        synth->setAR(2.0f, 1.0f);
    }

    ~CustomCallback() override {

    }

    void prepare (int sampleRate) override {
        synth->setSamplerate(sampleRate);
    }

    void process (AudioBuffer buffer) override {
        auto [inputChannels, outputChannels, numInputChannels, numOutputChannels, numFrames] = buffer;

        for (int sample = 0u; sample < numFrames; ++sample) { 
            synth->tick();
            float mixedSample = synth->getSample();

            for (int channel = 0u; channel < numOutputChannels; ++channel) {
                // write sample to buffer at channel 0, amp = 0.25
                outputChannels[channel][sample] = mixedSample;
            }

        }
    }


    Synth& getSynth() { return *synth; }
    void setSynth(std::unique_ptr<Synth> newSynth) {
        synth = std::move(newSynth);
    }

private:
    std::unique_ptr<Synth> synth;
};
