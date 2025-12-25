#ifndef SUBUI_H
#define SUBUI_H

#include "subSynth.h"
#include "customCallback.h"
#include <iostream>

class subUI {
public:
    subUI();
    ~subUI();
    
    void showHelp();
    void run();  // Takes SubSynth reference as parameter
    
private:
    Synth& synth;
};

#endif // SUBUI_H