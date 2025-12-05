#include "audiocomponent.h"
//  Daan Schrier
#include "sine.h"
#include "square.h"
#include "saw.h"
#include "oscillatorBank.h"

struct CustomCallback : AudioCallback {
    explicit CustomCallback (double Fs) : AudioCallback(Fs) {

    }

    ~CustomCallback() override {

    }

    void prepare (int sampleRate) override {

    }

    void addSine(float frequency) {
        bank.addOscillator(std::make_unique<Sine>(frequency, sampleRate));
    }

    void addSaw(float frequency) {
        bank.addOscillator(std::make_unique<Saw>(frequency, sampleRate));
    }

    void addSquare(float frequency) {
        bank.addOscillator(std::make_unique<Square>(frequency, sampleRate));
    }

    void clearOscillators() {
        bank.clear();
    }

    void removeOscillator(size_t index) {
        bank.removeOscillator(index);
    }

    void process (AudioBuffer buffer) override {
        auto [inputChannels, outputChannels, numInputChannels, numOutputChannels, numFrames] = buffer;

        for (int channel = 0u; channel < numOutputChannels; ++channel) {
            for (int sample = 0u; sample < numFrames; ++sample) {
                // write sample to buffer at channel 0, amp = 0.25
                outputChannels[channel][sample] = bank.getMixedSample();
                bank.tickAll();
            }
        }
    }

private:
    OscillatorBank bank;
};
