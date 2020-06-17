#include "MidiFile.h"
#include"cnpy.h"
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <complex>
#include <cstdlib>

#include "MidiDecoder.h"


MidiDecoder::MidiDecoder(){}

void MidiDecoder::load(const std::string& fileName){
    std::string midiData = "./data/classical.midi";
    MidiFileArray = createMidiArray(midiData);
}

void MidiDecoder::save(const std::string& fileName){

    std::vector<int> data(currentTick * midiInputRange);

    for(int i = 0; i < currentTick; i++) {
        for (int j = 0; j < midiInputRange; j++){
            data[i*midiInputRange + j] = MidiFileArray[i][j];
        }
    }

    cnpy::npy_save(fileName, &data[0], {currentTick, midiInputRange}, "w");
}


int** MidiDecoder::createMidiArray(const std::string& fileName){

    smf::MidiFile midifile(fileName);
    midifile.joinTracks();
   
    smf::MidiEvent* mev;
    smf::MidiEventList track = midifile[0];

    // Convert the midi data to absolute ticks. This means that time is measured
    // relative to the beginning of the file, not the previous event
    if (midifile.isAbsoluteTicks() < 1) {
        midifile.absoluteTicks();
    }

    // find the total tick length by finding the ticks of the final event
    mev = &track[track.size() - 2];
    int oldTickLength = mev->tick;

    int totalQuarterNotes = oldTickLength / midifile.getTicksPerQuarterNote();

    // we want there to only be a single tick per 16th note
    // TODO: that this needs to be specified in the new midi header
    int totalTicks = totalQuarterNotes * 8;
    double conversionRate = (oldTickLength / totalTicks);

    // Reduce the file into an array
    MidiFileArray = new int*[totalTicks + buffer];
    
    for (int y = 0; y <= totalTicks + buffer; y++){
        MidiFileArray[y] = new int[midiInputRange];
    }

    // currentick tracks where we are in the MidiFileArray
    // it is moved up once a midiEvent tick value is greater
    // than the currentTick value
    currentTick = 0;

    for (int event = 0; event < track.size(); event++) {

        mev = &track[event];
        int mevTickValue = mev->tick / conversionRate;

        if (currentTick <= mevTickValue && mevTickValue < currentTick + 1){

            // Check if midi event is to spawn a note, remove a note, or metadata
            int binaryCommand = (int)(*mev)[0];

            // Define pitch and velocity values
            int pitchValue    = (int)(*mev)[1];
            int velocityValue = (int)(*mev)[2];

            // determine if the given midi event is closer in time to the
            // currentTick or the next tick
            if (mevTickValue >= ((double) currentTick) + 0.5){
                mevTickValue = currentTick + 1;
            } else {
                mevTickValue = currentTick;
            }

            // Change the values in the array to 1 (on) or 0 (off)
            // depending on the given input
            if (mev->isNoteOn() == 1) {
                MidiFileArray[mevTickValue][pitchValue] = 1;
            } else if (mev->isNoteOff() == 1){
                MidiFileArray[mevTickValue][pitchValue] = 0;
            }

        } else {

            // If the midievent tick is higher than out current tick value, we should copy
            // the previous array/eventlist until the ticks are even becuase nothing has changed
            while (currentTick < mevTickValue) {
                for (int i = 0; i < midiInputRange; i++){
                    MidiFileArray[currentTick + 1][i] = MidiFileArray[currentTick][i];
                }
                currentTick++;
            }
            // Once we've reached the tick value of the next midi event,
            // reset to the midi event with the current tick value 
            event--;
        }
   }

   return MidiFileArray;
}

