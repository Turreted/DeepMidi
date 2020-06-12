#include <iostream>
#include <iomanip>
#include <string>

#include "MidiFile.h"


class Encoder{
private:
    MidiFile midifile; // yay

public:
    Encoder(string fileName);

    void encode() {};
    void format() {};
    void serialize(string fileName) {};
    void printMidiData(int len=1000) {};
};
