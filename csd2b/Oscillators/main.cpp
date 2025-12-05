#include <iostream>
#include <string>
#include "customCallback.h"

using namespace std;

int main() {
    ScopedMessageThreadEnabler scopedMessageThreadEnabler;
    CustomCallback audioSource (44100);
    JUCEModule juceModule (audioSource);
    juceModule.init(1,1);

    cout << "Start program" << endl;
    bool running = true;
    while (running) {
        string command, type;
        float value;
        cin >> command >> type >> value;
        if (command == "q") {
                running = false;
                break;
        }
        else if (command == "add") {
            switch (type) {}
                case "sin" : customCallback.addSine(value);
                case "saw" : customCallback.addSaw(value);
        }
    }

    return 0;
}
