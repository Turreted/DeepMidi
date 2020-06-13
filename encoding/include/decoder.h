#include <iostream>
#include <string>

#include "MidiFile.h"
#include"cnpy.h"


class Decoder{
    private:
        // dimensions of midi array
        int shape_y;
        int shape_x;

        // array object
        short int * loadedData;

    public:
        Decoder(std::string fileName);
        smf::MidiFile * reconstructMidiFile(int ** midiFileArray);
        int ** typecastInteger(cnpy::NpyArray &arr);
        void save(smf::MidiFile &midifile, std::string fileName);
};