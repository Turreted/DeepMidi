#ifndef MIDIENCODER_H
#define MIDIENCODER_H

#include <iostream>
#include <iomanip>
#include <string>

#include "MidiFile.h"


class MidiEncoder{
private:
    // Midi constants
    const static int TPQ = 16;
    const static int midiInputRange = 127;
    const static int buffer = 128;

    int currentTick;

    int** MidiFileArray;
    int** createMidiArray(const std::string& fileName);


public:

    void load(const std::string& fileName);
    void save(const std::string& fileName);
};

#endif