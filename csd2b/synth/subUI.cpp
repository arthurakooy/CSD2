#include "subUI.h"
#include <iostream>
#include <string>
using namespace std;

subUI::subUI() {
    synth = audioSource.getSynth();
};

subUI::~subUI() {
};

void subUI::showHelp() {
    cout << "\n=== SUBTRACTIVE SYNTH COMMANDS ===" << endl;
    cout << "add <type> <level> <detune>" << endl;
    cout << "clear" << endl;
    cout << "filter <hz>" << endl;
    cout << "setAR <attack> <release>" << endl;
    cout << "note <midi>" << endl;
    cout << "off" << endl;
    cout << "help" << endl;
    cout << "q" << endl;
};

// Process one command, return true to continue, false to quit
void subUI::run() {
    string command;
    cin >> command;

    if (command == "help") {
        showHelp();
    }
    else if (command == "clear") {
        synth.clearOscillators();
        cout << "Oscillators cleared" << endl;
    }
    else if (command == "filter") {
        float value;
        cin >> value;
        synth.setFilterCutoff(value);
        cout << "Filter cutoff: " << value << " Hz" << endl;
    }
    else if (command == "add") {
        string type;
        float level;
        float detune;
        cin >> type >> level >> detune;

        synth.addOscillator(type, level, detune);
        cout << "Added " << type << " oscillator" << endl;
    }
    else if (command == "setAR") {
        float attack;
        float release;
        cin >> attack >> release;

        synth.setAR(attack, release);
        cout << "Attack: " << attack << "s, Release: " << release << "s" << endl;
    }
    else if (command == "note") {
        float note;
        cin >> note;
        synth.playNote(note, 0.8f);
        cout << "Playing note: " << note << endl;
    }
    else if (command == "off") {
        synth.noteOff();
        cout << "Note released" << endl;
    }
    else {
        cout << "Command not found. Type 'help'." << endl;
    }
};