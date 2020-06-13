#include <iostream>
#include <iomanip>
#include <string>

#include "MidiFile.h"


class Encoder{
private:
    stf::MidiFile midifile;

public:
    Encoder(std::string fileName);

    void encode() {};
    void format() {};
    void serialize(std::string fileName) {};
};
