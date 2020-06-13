#include "MidiFile.h"
#include"cnpy.h"
#include <iostream>
#include <iomanip>
#include <string>
#include <complex>

#include "decoder.h"


Decoder::Decoder(std::string fileName){

    cnpy::NpyArray arr = cnpy::npy_load(fileName);
    this->loadedData = arr.data<short int>();

    this->shape_y = arr.shape[0];
    this->shape_x = arr.shape[1];
}

smf::MidiFile * Decoder::reconstructMidiFile(int ** midiFileArray){
    smf::MidiFile midifile;
    
    int track      = 0;
    int channel    = 0;
    int instrument = 0; // Defaults to 0, the piano


    midifile.addTimbre(track, 0, channel, instrument);

    // measured by 32nd note
    int TPQ = 8;
    midifile.setTicksPerQuarterNote(8);

    //velocity is constant
    int velocity = 100;
    //
    int currentState = 0;


    // go column by column
    for (int note = 0; note < shape_x; ++note){
        for (int tick = 0; tick < shape_y; ++tick){

            if (midiFileArray[tick][note] != currentState){

                // Check to see if a note is being turned on or off
                if (currentState == 0){
                    midifile.addNoteOn(track, tick, channel, note, velocity);
                } else if (currentState == 1){
                    midifile.addNoteOff(track, tick, channel, note);
                }
                // Set currentState to note on or off
                currentState = midiFileArray[tick][note];
            }
        }
        // Turn currentState to note off
        currentState = 0;
    }

    midifile.sortTracks();  // Need to sort tracks since added events are
                           // appended to track in random tick order.
    return &midifile;
}

void Decoder::save(smf::MidiFile &midifile, std::string fileName){
    midifile.write(fileName);
}


// Converts the cnpy object into a 2d array of integers.
// This function assumes that the array is 2d
int ** Decoder::typecastInteger(cnpy::NpyArray &arr){

    int ** integerArray = new int*[arr.shape[0]];
    
    for (int y = 0; y < arr.shape[0]; ++y){
        integerArray[y] = new int[shape_x];

        for (int x = 0; x < arr.shape[1]; ++x){
            int loadedDataIndex = (y * shape_x) + x;
            integerArray[y][x] = loadedData[loadedDataIndex];
        }
    }

    return integerArray;
}
