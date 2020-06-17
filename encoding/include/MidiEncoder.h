#ifndef MIDIENCODER_H
#define MIDIENCODER_H

#include <iostream>
#include <string>

#include "MidiFile.h"
#include"cnpy.h"


class MidiEncoder{
    private:
        // Midi constants
        const static int TPQ = 16;
        const static int midiInputRange = 127;
        const static int buffer = 128;

        // dimensions of midi array
        int shape_y;
        int shape_x;

        smf::MidiFile midifile;

        smf::MidiFile reconstructMidiFile(int** midiFileArray);
        int** typecastInteger(cnpy::NpyArray* arr);

    public:
        void load(const std::string& filename);
        void save(const std::string& fileName);
};

#endif
