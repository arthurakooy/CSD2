#include "audiocomponent.h"
//  Daan Schrier
#include "subSynth.h"
#include "fmSynth.h"
#include "synth.h"
#include "melody.h"
#include "note.h"
#include <memory>

struct CustomCallback : AudioCallback {
    explicit CustomCallback (double Fs) : AudioCallback(Fs) {
        // synth.setSamplerate(Fs);

        // // test stuffz
        // synth.addOscillator("saw", 0.8f, 0.0f);
        // synth.addOscillator("square", 0.5f, -12.0f);
        // synth.setAR(2.0f, 1.0f);
        // synth.setFilterCutoff(2000.0f);

        synth = std::make_unique<Synth>(Fs); //create temporary synth to overwrite, probably not the best way but idgaf

    }

    ~CustomCallback() override {

    }

    void prepare (int sampleRate) override {
        synth->setSamplerate(static_cast<float>(sampleRate));
        melody.prepare(sampleRate);
    }

    void process (AudioBuffer buffer) override {
        auto [inputChannels, outputChannels, numInputChannels, numOutputChannels, numFrames] = buffer;

        for (int sample = 0u; sample < numFrames; ++sample) { 
            synth->tick();
            if(melody.tick()) {
                Note note = melody.getCurrentNote();
                int midiNote = note.getMidiNoteNumber();
                synth->playNote(midiNote, 0.6);
            }
            if(melody.getNoteOff()) {
                synth->noteOff();
            }

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
    Melody melody;
};
