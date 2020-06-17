#include <iostream>
#include <string>

#include "MidiFile.h"
#include"cnpy.h"


class MidiEncoder{
    private:
        // dimensions of midi array
        int shape_y;
        int shape_x;

        smf::MidiFile midifile;

        smf::MidiFile reconstructMidiFile(int** midiFileArray);
        int** typecastInteger(cnpy::NpyArray* arr);

    public:
        MidiEncoder(const std::string& fileName);

        void load(const std::string& filename);
        void save(const std::string& fileName);
};