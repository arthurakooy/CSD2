#ifndef _FMSYNTH_H_
#define _FMSYNTH_H_
#include "synth.h"
#include "sine.h"
#include <cmath>
#include <memory>  // for unique_ptr

class FmSynth : public Synth {
public: 
    FmSynth(float samplerate = 44100.0f);
    ~FmSynth();

    void tick() override;
    void setSamplerate(float samplerate) override;
    void setRatio(float ratio);
    void setModulationIndex(float modulationIndex);
    // void setCarrier(std::string type = "sine");
    // void setCarrier(std::string type = "sine");

    void playNote(float note, float amplitude) override;

protected:
    std::unique_ptr<Sine> carrierOsc;
    std::unique_ptr<Sine> modulatorOsc;
    float modulationIndex;
    float ratio;
};


#endif