#ifndef OSCILLATORBANK_H
#define OSCILLATORBANK_H

#include <vector>
#include <memory>
#include "oscillator.h"

class OscillatorBank {
public:
    void addOscillator(std::unique_ptr<Oscillator> osc) {
        oscillators.push_back(std::move(osc));
    }

    void updateAllPhases() {
        for (auto& osc : oscillators) {
            osc->updatePhase();
        }
    }

    float getMixedSample() {
        float mixed = 0.0f;
        for (auto& osc : oscillators) {
            mixed += osc->calculateSample();
        }
        return mixed / oscillators.size();
    }

    void tickAll() {
        for (auto& osc : oscillators) {
            osc->tick();
        }
    }

    void clear() {
        oscillators.clear();
    }

    void removeOscillator(size_t index) {
        if(index < oscillators.size()) {
            oscillators.erase(oscillators.begin() + index);
        }
    }

private:
    std::vector<std::unique_ptr<Oscillator>> oscillators;
};

#endif