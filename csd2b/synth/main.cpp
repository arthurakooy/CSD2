#include <iostream>
#include "customCallback.h"
#include "subSynth.h"
#include "fmSynth.h"
#include <string>
// #include "subUI.h"

using namespace std;

int main() {
    float sampleRate = 44100.0f;
    ScopedMessageThreadEnabler scopedMessageThreadEnabler;
    CustomCallback audioSource (sampleRate);

    cout << "=== INITIALIZE SYNTH ===" << endl;
    cout << endl;
    
    // select type
    cout << "Choose synth type:" << endl;
    cout << "1. Subtractive synth" << endl;
    cout << "2. FM synth" << endl;
    cout << "Enter choice (1 or 2): ";
    
    string choice;
    cin >> choice;
    
    
    while(true) {
        if (choice == "1") {
            auto subSynth = make_unique<SubSynth>(sampleRate);

            cout << "Add oscillators" << endl;
            cout << "add <type> <level> <detune>" << endl;
            cout << "type 'done' to continue" << endl;
            while(true) {
                string command;
                cin >> command;
                if (command == "add") {
                    string type;
                    float level;
                    float detune;
                    cin >> type >> level >> detune;

                    subSynth->addOscillator(type, level, detune);
                    cout << "Added " << type << " oscillator" << endl;
                } 
                else if (command == "done") {
                    break;
                } 
                else {
                    cout << "Invalid input" << endl;
                }

                
            }

            // initialize filter
            cout << "Enter filter cutoff in Hz" << endl;
            cout << "<Hz>" << endl;
            float value;
            cin >> value;
            subSynth->setFilterCutoff(value);
            cout << "Filter cutoff: " << value << " Hz" << endl;

            // initialize envelope
            cout << "Enter attack and release" << endl;
            cout << "<attack> <release>" << endl;
            float attack, release; 
            cin >> attack >> release;
            subSynth->setAR(attack, release);
            cout << "Attack: " << attack << "s, Release: " << release << "s" << endl;

            // create subSynth
            audioSource.setSynth(move(subSynth));

            cout << "Subtractive synth created!" << endl;
            break;
        }
        else if (choice == "2") {
            auto fmSynth = make_unique<FmSynth>(sampleRate);

            // initialize ratio
            cout << "Enter ratio" << endl;
            cout << "<ratio>" << endl;
            float ratio;
            cin >> ratio;
            fmSynth->setRatio(ratio);

            // initialze modulation index
            cout << "enter modulation index" << endl;
            cout << "<modIndex>" << endl;
            float modIndex;
            cin >> modIndex;
            fmSynth->setModulationIndex(modIndex);

            // initialize envelope
            cout << "Enter attack and release" << endl;
            cout << "<attack> <release>" << endl;
            float attack, release;
            cin >> attack >> release;
            fmSynth->setAR(attack, release);
            cout << "Attack: " << attack << "s, Release: " << release << "s" << endl;

            // create fmSynth
            audioSource.setSynth(move(fmSynth));

            cout << "FM synth created!" << endl;
            break;
        }
        else {
            cout << "Invalid choice." << endl;
            cin >> choice;
        }


    }
    
    JUCEModule juceModule (audioSource);
    juceModule.init(2,2);

    Synth& synth = audioSource.getSynth();

    cout << "=== STARTING SYNTH ===" << endl;

    bool running = true;

    while (running) {
        string command;
        cin >> command;

        if(command == "q") {
            running = false;
        }
    
        // FOR MANUAL TESTING

        // else if(command == "a") {
        //     synth.playNote(60, 0.8);
        // }

        // else if(command == "r") {
        //     synth.noteOff();
        // }
        else {
            cout << "Command not found. Type 'help'." << endl;
        }
    }

    return 0;
}
